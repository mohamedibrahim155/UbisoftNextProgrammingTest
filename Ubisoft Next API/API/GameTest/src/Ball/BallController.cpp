#include "stdafx.h"
#include "BallController.h"
#include "../InputManager/InputManager.h"
#include "../Utils/PhysicsUtils.h"

BallController::BallController(Ball* ballComponent):
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

void BallController::initialize(RigidBody* ballphysics, SpriteRenderer* ballSprite, CircleCollider* collider, EntityManager* entityManager)
{
	this->pRigidBody = ballphysics;
	this->pSprite = ballSprite;
	this->pCollider = collider;
	this->pEntityManager = entityManager;
    this->pGameObject = pBall->getEntity();

	m_initalPosition = pGameObject->transform.position;

	subscribeCollisionEvent();
	initializePool();
}

void BallController::subscribeCollisionEvent()
{
	pCollider->OnCollision.Subscribe([this](Collider* otherCollider)
		{
			onCollisionStay(otherCollider);
		});
}

void BallController::initializePool()
{
	Entity* projectileBallPrefab = pEntityManager->createEntity();
	SpriteRenderer* circleSprite = new SpriteRenderer(CIRCLE_PATH, true);

	projectileBallPrefab->addComponent(circleSprite);
	projectileBallPrefab->setActive(false);
	projectileBallPrefab->transform.scale = Vector2(0.05f, 0.05f);


	pEntityPool = new EntityPool(pEntityManager, projectileBallPrefab);
	pEntityPool->setScaleForEntities(Vector2(0.05f, 0.05f));
}

#pragma endregion


void BallController::handleAim()
{

	switch (m_state)
	{
	case eBallState::IDLE:
		idleState();
		break;
		break;
	case eBallState::AIMING:
		aimState();
		break;
	case eBallState::SHOOTING:
		shootState();
		break;

	default:
		setState(eBallState::IDLE);
		break;
	}
#pragma region OldCode



	//if (m_state != BallState::IDLE && m_state != BallState::AIMING) return;

	//if (InputManager::GetInstance().getKeyDown(VK_LBUTTON))
	//{
	//	m_state = BallState::AIMING;
	//	Vector2 pos = { pGameObject->transform.position.x + m_centerScreen.x, pGameObject->transform.position.y + m_centerScreen.y };

	//	m_renderLine.startPoint = Vector2(pos.x, pos.y);


	//}
	//if (InputManager::GetInstance().getKey(VK_LBUTTON))
	//{
	//	Vector2 mousePosition = InputManager::GetInstance().getMousePosition();
	//	Vector2 currentPosition = m_renderLine.startPoint - mousePosition;

	//	float length = currentPosition.Magnitude();

	//	currentPosition = (length > m_maxLineThreshold) ?
	//		currentPosition.Normalize() * m_maxLineThreshold : currentPosition.Normalize() * length;

	//	m_renderLine.endPoint = m_renderLine.startPoint - currentPosition;

	//	m_aimDirection = m_renderLine.startPoint - m_renderLine.endPoint;
	//}

	//if (InputManager::GetInstance().getKeyUp(VK_LBUTTON))
	//{
	//	m_renderLine = { Vector2::Zero(), Vector2::Zero() };


	//	
	//	
	//	shootBall(m_aimDirection);
	//	m_state = BallState::SHOOTING;
	//}
#pragma endregion


}

void BallController::stopBall()
{
	pRigidBody->velocity = Vector2::Zero();
}

void BallController::reset()
{
	pGameObject->transform.position = m_initalPosition;
	pRigidBody->velocity = Vector2::Zero();
	m_state = eBallState::IDLE;
}

void BallController::renderTrajectory()
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
		trajectoryEntity->transform.position = position - m_centerScreen;
	}
}

void BallController::resetPoolEntites()
{
	std::vector<Entity*> activeEntities = pEntityPool->getActiveEntites();

	// Deactivate all active trajectory entities before recalculating positions
	for (Entity* entity : activeEntities)
	{
		pEntityPool->destroyObject(entity);
	}
}

void BallController::shootBall(Vector2 direction)
{
	if (direction.Magnitude() <= 0.01f) return; // Prevent shooting when no direction

	float bounceSpeed = calculateBounceSpeed(direction);

	pRigidBody->velocity += direction.Normalize() * bounceSpeed;
	
}



bool BallController::isMoving()
{
	return pRigidBody->velocity.Magnitude() > m_stoppingFactor;
}

bool BallController::isInRange()
{

	Vector2 mousePosition = InputManager::GetInstance().getMousePosition();

	Vector2 center = pCollider->getCircle().centre;

	Vector2 diff = center - mousePosition;

	float dot = diff.x * diff.x + diff.y * diff.y;

	return dot < m_cursoeRadius * m_cursoeRadius;
}

#pragma region States

void BallController::aimState()
{

	if (InputManager::GetInstance().getKey(VK_LBUTTON))
	{
		if (isInRange())
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
		if (isInRange())
		{
			m_projectileLine = { Vector2::Zero(), Vector2::Zero() };
			shootBall(m_aimDirection);

			setState(eBallState::SHOOTING);
		}
		else
		{
			setState(eBallState::IDLE);
		}

		resetPoolEntites();

	}
}

void BallController::shootState()
{
	if (!isMoving())
	{
		stopBall();

		m_state = eBallState::IDLE;
	}
}

void BallController::idleState()
{
	if (isInRange() && InputManager::GetInstance().getKeyDown(VK_LBUTTON))
	{
		// Initialize the aiming line starting point
		Vector2 pos = { pGameObject->transform.position.x + m_centerScreen.x,
						pGameObject->transform.position.y + m_centerScreen.y };

		m_projectileLine.startPoint = pos;

		setState(eBallState::AIMING); // Transition to Aiming state

	}

	//Deactivates projectile on screen
	resetPoolEntites();
}

void BallController::setState(eBallState nextState)
{
	if (m_state != nextState)
	{
		m_state = nextState;
	}
}

std::string BallController::getState()
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


void BallController::onCollisionStay(Collider* collider)
{
	
}





float BallController::calculateBounceSpeed(Vector2 aimDir)
{
	float length = aimDir.Magnitude();

	float percentage = length / m_maxLineThreshold;

	float speed = percentage * m_bounceSpeed;

	return speed;
}