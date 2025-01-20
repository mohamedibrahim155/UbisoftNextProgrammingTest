#include "stdafx.h"
#include "Ball.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/InputManager/InputManager.h"
#include "../src/Ball/BallController.h"

Ball::Ball(EntityManager* entityManager, eColorType type) : BaseScriptComponent(), m_intialBallType(type)
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

	Vector2 mousePos = InputManager::GetInstance().getMousePosition();
	std::string total = std::to_string(mousePos.x) + " " + std::to_string(mousePos.y);
	App::Print(100, 100, total.c_str(), 1, 1, 1);
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
	
	//Sets rigid body properties
	rigidBody->bounciness = 1;
	rigidBody->setMass (20);
	rigidBody->setGravity(0);

	// add the components to the gameObject
	gameObject->addComponent(ballSprite);
	gameObject->addComponent(circleCollider);
	gameObject->addComponent(rigidBody);

	//Sets initial Position
	gameObject->transform.position = m_spawnPosition;


	//Creating controller
	controller = new BallController(this);
	controller->initialize(entityManager);
	controller->setType(m_intialBallType);
}



