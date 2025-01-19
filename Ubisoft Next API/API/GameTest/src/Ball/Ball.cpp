#include "stdafx.h"
#include "Ball.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/InputManager/InputManager.h"
#include "../src/Ball/BallController.h"

Ball::Ball(EntityManager* entityManager) : BaseScriptComponent()
{
	this->entityManager = entityManager;
}

void Ball::start()
{

	createBall();

}

void Ball::updateComponent()
{
	
	if (!controller) return;

	controller->handleAim(); 

}

void Ball::render(bool isDebugVisible)
{
	if (!controller) return;

	bool isInRange = controller->isInRange();

	if (isInRange)
	{
		controller->renderTrajectory();

	}
	else
	{
		controller->resetPoolEntites();
	}

	if (!isDebugVisible) return;
	std::string total = rigidBody ? std::to_string(rigidBody->velocity.x) + " " + std::to_string(rigidBody->velocity.y) : " ";
	App::Print(100, 100, controller->getState().c_str(), 1, 1, 1);
}

void Ball::cleanUp()
{
	if (controller)
	{
		delete controller;
	}
}

void Ball::setSpawnPosition(const float& x, const float& y)
{
	m_spawnPosition.x = x;
	m_spawnPosition.y = y;
}

void Ball::createBall()
{
	// Set Tag
	gameObject->setTag("Ball");

	// Creates the components needed to the ball
	ballSprite = new SpriteRenderer(BALL_TEXTURE_PATH,Vector2::Zero(), 5);
	circleCollider = new CircleCollider();
	rigidBody = new RigidBody(eBodyType::DYNAMIC);
	std::string defaultCircle = ASSET_PATH + "\\Default\\circle-512.png";
	particleComponent = new ParticleComponent(defaultCircle,50,1);

	particleComponent->m_colorX = 1;
	particleComponent->m_colorY = 0;
	particleComponent->m_colorZ = 1;
	particleComponent->m_spawnRadius = 1;
	particleComponent->m_gravity = -3;
	particleComponent->m_scale = 0.008f;

	particleComponent->m_startVelocityX = { -300, 300 };
	particleComponent->m_startVelocityY = { -300, 300 };
	particleComponent->m_startTime = { 0.5,1 };
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
	controller->initialize(entityManager);
}



