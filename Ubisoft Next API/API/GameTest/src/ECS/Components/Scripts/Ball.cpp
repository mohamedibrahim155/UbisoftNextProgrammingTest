#include "stdafx.h"
#include "Ball.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/InputManager/InputManager.h"

void Ball::start()
{
	gameObject->setTag("Ball");
	createBallSprite();
}

void Ball::updateComponent()
{
	updateInput();
}

void Ball::render(bool isDebugVisible)
{
}

void Ball::cleanUp()
{
}

void Ball::createBallSprite()
{

	SpriteRenderer* ballSprite = new SpriteRenderer(ballTexture,Vector2::Zero(), 5);
	Collider* circleCollider = new CircleCollider();
	rigidBody = new RigidBody(eBodyType::DYNAMIC);
	rigidBody->bounciness = 1;
	rigidBody->SetMass (20);
	rigidBody->SetGravity(0);

	gameObject->addComponent(ballSprite);
	gameObject->addComponent(circleCollider);
	gameObject->addComponent(rigidBody);
}

void Ball::updateInput()
{
	if (InputManager::GetInstance().GetKeyDown(VK_LEFT))
	{
		rigidBody->velocity.x -= 20;
	}
	if (InputManager::GetInstance().GetKeyDown(VK_RIGHT))
	{
		rigidBody->velocity.x += 20;
	}
	if (InputManager::GetInstance().GetKeyDown(VK_UP))
	{
		rigidBody->velocity.y += 20;
	}

	if (InputManager::GetInstance().GetKeyDown(VK_DOWN))
	{
		rigidBody->velocity.y -= 20;
	}

	if (InputManager::GetInstance().GetKeyDown(VK_SPACE)) 
	{
		rigidBody->velocity.y = 0;
	}
	if (InputManager::GetInstance().GetKeyUp(VK_DOWN))
	{
		rigidBody->velocity.y = 0;
	}
}
