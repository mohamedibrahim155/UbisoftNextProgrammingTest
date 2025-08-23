#include "stdafx.h"
#include "Ball.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/InputManager/InputManager.h"
#include "../src/Ball/BallController.h"

BallComponent::BallComponent(EntityManager* entityManager, eColorType type) : BaseScriptComponent(), m_intialBallType(type)
{
	this->entityManager = entityManager;
}

void BallComponent::start()
{

	createBall();

}

void BallComponent::updateComponent()
{
	
	if (!controller) return;

	controller->updateAim(); 

}

void BallComponent::render(bool isDebugVisible)
{
	if (!controller) return;

	bool isInRange = controller->isWithinCursorRange();

	if (isInRange)
	{
		controller->renderAimLine();

	}
	else
	{
		controller->resetPoolEntites();
	}

	if (!isDebugVisible) return;

	Vector2 mousePos = InputManager::GetInstance().getMousePosition();
	std::string total = std::to_string(mousePos.x) + " " + std::to_string(mousePos.y);
	App::Print(100, 100, total.c_str(), 1, 1, 1);
}

void BallComponent::cleanUp()
{
	if (controller)
	{
		delete controller;
	}
}

void BallComponent::setSpawnPosition(const float& x, const float& y)
{
	m_spawnPosition.x = x;
	m_spawnPosition.y = y;
}

void BallComponent::createBall()
{
	// Set Tag
	gameObject->setTag("Ball");

	// Creates the components needed to the ball
	ballSprite = new SpriteRenderer(BALL_TEXTURE_PATH,Vector2::Zero(), 5);
	circleCollider = new CircleCollider();
	rigidBody = new RigidBody(eBodyType::DYNAMIC);

	particleComponent = new ParticleComponent(PARTICLE_PATH, 50, 1);

	particleComponent->m_colorX = 1;
	particleComponent->m_colorY = 1;
	particleComponent->m_colorZ = 1;
	particleComponent->m_spawnRadius = 1;
	particleComponent->m_gravity = -3;
	particleComponent->m_scale = 0.005f;
	particleComponent->m_startVelocityX = { -600, 600 };
	particleComponent->m_startVelocityY = { -600, 600 };
	particleComponent->m_startTime = { 0.1,0.2 };
	particleComponent->playOnAwake = false;

	//Sets rigid body properties
	rigidBody->bounciness = 1;
	rigidBody->setMass (20);
	rigidBody->setGravity(0);

	// add the components to the gameObject
	gameObject->addComponent(ballSprite);
	gameObject->addComponent(circleCollider);
	gameObject->addComponent(rigidBody);
	gameObject->addComponent(particleComponent);

	//Sets initial Position
	gameObject->transform.position = m_spawnPosition;


	//Creating controller
	controller = new BallController(this);
	controller->init(entityManager);
	controller->setColorType(m_intialBallType);
}



