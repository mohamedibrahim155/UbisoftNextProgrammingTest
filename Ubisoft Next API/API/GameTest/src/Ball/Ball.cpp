#include "stdafx.h"
#include "Ball.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/InputManager/InputManager.h"
#include "../src/Ball/BallController.h"

Ball::Ball() : BaseScriptComponent()
{
}

void Ball::start()
{

	createBall();

}

void Ball::updateComponent()
{
	
	if (!controller) return;

	controller->handleAim(); // Handles aiming and shooting logic
	//controller->restBall(); // Handles resetting after the ball stops


}

void Ball::render(bool isDebugVisible)
{
	if (!controller) return;

	bool isInRange = controller->cursorInsideRadius();

	if (isInRange)
	{
		controller->renderTrajectory();

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



void Ball::createBall()
{
	// Set Tag
	gameObject->setTag("Ball");

	// Creates the components needed to the ball
	ballSprite = new SpriteRenderer(ballTexture,Vector2::Zero(), 5);
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

	gameObject->transform.position = m_spawnPosition;


	//Creating controller
	controller = new BallController(this);
	controller->initialize(rigidBody, ballSprite, (CircleCollider*)circleCollider);
}



