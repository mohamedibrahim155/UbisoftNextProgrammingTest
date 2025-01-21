///////////////////////////////////////////////////////////////////////////////
// Filename: BallController.cpp
// Controls the ball's movement and behavior
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "BallController.h"
#include "../InputManager/InputManager.h"
#include "../Utils/PhysicsUtils.h"
#include "../src/GameManager/GameManager.h"
#include "../src/Block/Blocks.h"
#include "../src/LevelManager/LevelManager.h"


BallController::BallController(BallComponent* ballComponent):
	pBall(ballComponent),
    pRigidBody(nullptr), 
    pSprite(nullptr)
{
}

BallController::~BallController()
{
	if (pEntityPool)
	{
		delete pEntityPool;
	}
}

#pragma region Init

// Intial references from Ball
void BallController::init(EntityManager* entityManager)
{
	this->pEntityManager = entityManager;
    this->pGameObject = pBall->getEntity();

	//intial references
	this->pRigidBody = (RigidBody*)pGameObject->getComponent(eComponentType::PHYSICS_COMPONENT);
	this->pSprite = (SpriteRenderer*)pGameObject->getComponent(eComponentType::RENDER_COMPONENT);
	this->pCollider = (CircleCollider*)pGameObject->getComponent(eComponentType::COLLIDER_COMPONENT);
	this->pParticle = (ParticleComponent*)pGameObject->getComponent(eComponentType::PARTICLE_COMPONENT);

	m_initalPosition = pGameObject->transform.position;

	subscribeEvents();
	initPool();

}

// Subscribes global events
void BallController::subscribeEvents()
{
	pCollider->OnCollisionEnter.Subscribe([this](Collider* otherCollider)
		{
			onCollisionEnter(otherCollider);
		});

	GameManager::GetInstance().onStrokeCompleted.Subscribe([this]() 
		{
			isGameOver = true;
		});
}

// create a prefab and creates Object pooling
void BallController::initPool()
{
	Entity* projectileBallPrefab = pEntityManager->createEntity();
	SpriteRenderer* circleSprite = new SpriteRenderer(BALL_SPRITE_PATH, true);

	projectileBallPrefab->addComponent(circleSprite);
	projectileBallPrefab->setActive(false);
	projectileBallPrefab->transform.scale = Vector2(0.05f, 0.05f);


	pEntityPool = new EntityPool(pEntityManager, projectileBallPrefab);
	pEntityPool->setScaleForEntities(Vector2(0.025f, 0.025f));
}

#pragma endregion

// State's handling - could have been in stateMachine
void BallController::updateAim()
{

	switch (m_state)
	{
	case eBallState::IDLE:
		onIdleState();
		break;
		break;
	case eBallState::AIMING:
		onAimState();
		break;
	case eBallState::SHOOTING:
		onShootState();
		break;

	default:
		setCurrentState(eBallState::IDLE);
		break;
	}


}

// force stops the ball
void BallController::haltBall()
{
	pRigidBody->velocity = Vector2::Zero();
}

// resets the ball data's
void BallController::reset()
{
	pGameObject->transform.position = m_initalPosition;
	pRigidBody->velocity = Vector2::Zero();
	m_state = eBallState::IDLE;
}

// renders the trajectory line which uses object pool
void BallController::renderAimLine()
{
	if (m_state != eBallState::AIMING) return;

	Vector2 trajectoryStart = m_projectileLine.startPoint;

	float length = MathF::Min(m_aimDirection.Magnitude(), m_maxLineThreshold);

	Vector2 trajectoryDirection = m_aimDirection.Normalize() * length *0.5f;

	resetPoolEntites();

	for (float t = 0; t < 2.0f; t += 0.2f) // Simulate for 2 seconds
	{
		// Calculate the position of the current trajectory point
		Vector2 position = trajectoryStart - trajectoryDirection * t;

		// Get a new or reused entity from the pool
		Entity* trajectoryEntity = pEntityPool->getEntity();
		if (!trajectoryEntity) continue;

		// Set the position of the trajectory entity
		Vector2 scale = trajectoryEntity->transform.scale * (2.0f - t);
		trajectoryEntity->transform.position = position - m_centerScreen;
		trajectoryEntity->transform.scale = scale;
	}
}

// resets pool to inactive state
void BallController::resetPoolEntites()
{

	std::vector<Entity*> activeEntities = pEntityPool->getActiveEntites();

	// Deactivate all active trajectory entities before recalculating positions
	for (Entity* entity : activeEntities)
	{
		pEntityPool->destroyObject(entity);

	}

	pEntityPool->setScaleForEntities(Vector2(0.025f, 0.025f));
}

// shoots ball based on Aimed direction
void BallController::launchBall(Vector2 direction)
{
	if (direction.Magnitude() <= 0.01f) return; // Prevent shooting when no direction

	float bounceSpeed = calculateBounceVelocity(direction);

	pRigidBody->velocity += direction.Normalize() * bounceSpeed;
	
	//updates strike 
	GameManager::GetInstance().updateStrike();
}


// checks if its moving
bool BallController::isMoving()
{
	return pRigidBody->velocity.Magnitude() > m_stoppingFactor;
}

// checks if the cursor is near to ball's position
bool BallController::isWithinCursorRange()
{

	Vector2 mousePosition = InputManager::GetInstance().getMousePosition();

	Vector2 center = pCollider->getCircle().centre;

	Vector2 diff = center - mousePosition;

	float dot = diff.x * diff.x + diff.y * diff.y;

	return dot < m_cursoeRadius * m_cursoeRadius;
}

#pragma region States

// Handles Idle state
void BallController::onIdleState()
{
	if (isWithinCursorRange() && InputManager::GetInstance().getKeyDown(VK_LBUTTON))
	{
		// Initialize the aiming line starting point
		Vector2 pos = { pGameObject->transform.position.x + m_centerScreen.x,
						pGameObject->transform.position.y + m_centerScreen.y };

		m_projectileLine.startPoint = pos;

		setCurrentState(eBallState::AIMING); // Transition to Aiming state

	}

	//Deactivates projectile on screen
	resetPoolEntites();
}

// Handles Aim state
void BallController::onAimState()
{

	if (InputManager::GetInstance().getKey(VK_LBUTTON))
	{
		if (isWithinCursorRange())
		{
			Vector2 mousePosition = InputManager::GetInstance().getMousePosition();
			Vector2 currentPosition = m_projectileLine.startPoint - mousePosition;

			float length = currentPosition.Magnitude();

			currentPosition = (length > m_maxLineThreshold) ?
				currentPosition.Normalize() * m_maxLineThreshold : currentPosition.Normalize() * length;

			m_projectileLine.endPoint = m_projectileLine.startPoint - currentPosition;

			m_aimDirection = m_projectileLine.startPoint - m_projectileLine.endPoint;
		}
		
	}

	if (InputManager::GetInstance().getKeyUp(VK_LBUTTON))
	{
		if (isWithinCursorRange())
		{
			m_projectileLine = { Vector2::Zero(), Vector2::Zero() };
			launchBall(m_aimDirection);
			setCurrentState(eBallState::SHOOTING);

		}
		else
		{
			setCurrentState(eBallState::IDLE);
		}

		resetPoolEntites();

	}
}

// Handles Shooting state
void BallController::onShootState()
{
	if (!isMoving())
	{
		haltBall();

		m_state = eBallState::IDLE;

		checkGameOver();
	}
}

// Handles game over state
void BallController::checkGameOver()
{
	
	if (isGameOver)
	{
		GameManager::GetInstance().gameOver();
		isGameOver = false;

		return;
	}
}

// Changes state if current != previous
void BallController::setCurrentState(eBallState nextState)
{
	if (m_state != nextState)
	{
		m_state = nextState;
	}
}

// return the current state as string
std::string BallController::getCurrentState()
{
	switch (m_state)
	{
	case eBallState::IDLE:
		return "IDLE";
	case eBallState::AIMING:
		return "AIMING";
	case eBallState::SHOOTING:
		return "SHOOTING";
	default:
		return "default";
	}
}

#pragma endregion



// Handle collision enter
void BallController::onCollisionEnter(Collider* collider)
{
	// checks ball collides with Block
	if (collider->getEntity()->getTag() == "Block")
	{
		Block* script = (Block*)collider->getEntity()->getComponent(eComponentType::SCRIPT_COMPONENT);
		
		if (script)
		{
			eColorType blockType = script->getType();
			if (m_type != blockType)
			{
				setColorType(blockType);

				
				Vector3 color = blockType == eColorType::WHITE ? Vector3::One() * 0.5f : Vector3::One();


				pParticle->m_colorX = color.x;
				pParticle->m_colorY = color.y;
				pParticle->m_colorZ = color.z;

				pParticle->Play(); // triggers particle 
			}
		}
	}
}


//change the color type and updates sprite color
void BallController::setColorType(eColorType type)
{
	m_type =type;

	updateSpriteColor(type);
}

//sets sprite color based on type
void BallController::updateSpriteColor(eColorType type)
{
	if (!pSprite) return;

	Vector3 color = Vector3::One();
	pSprite->setColor(type == eColorType::WHITE ? color : color * 0.5f);

	
}


// returns velocity based on dragged line
float BallController::calculateBounceVelocity(Vector2 aimDir)
{
	float length = aimDir.Magnitude();

	float percentage = length / m_maxLineThreshold;

	float speed = percentage * m_bounceSpeed;

	return speed;
}