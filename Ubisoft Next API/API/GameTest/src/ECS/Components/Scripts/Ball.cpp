#include "stdafx.h"
#include "Ball.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/InputManager/InputManager.h"

void Ball::start()
{
	
	createBall();
}

void Ball::updateComponent()
{
	handleAim();
	updateInput();
}

void Ball::render(bool isDebugVisible)
{
	renderLine();
}

void Ball::cleanUp()
{
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
	rigidBody->SetMass (20);
	rigidBody->SetGravity(0);

	// add the components to the gameObject
	gameObject->addComponent(ballSprite);
	gameObject->addComponent(circleCollider);
	gameObject->addComponent(rigidBody);
}

void Ball::updateInput()
{
	if (InputManager::GetInstance().getKeyDown(VK_LEFT))
	{
		rigidBody->velocity.x -= 20;
	}
	if (InputManager::GetInstance().getKeyDown(VK_RIGHT))
	{
		rigidBody->velocity.x += 20;
	}
	if (InputManager::GetInstance().getKeyDown(VK_UP))
	{
		rigidBody->velocity.y += 20;
	}

	if (InputManager::GetInstance().getKeyDown(VK_DOWN))
	{
		rigidBody->velocity.y -= 20;
	}

	if (InputManager::GetInstance().getKeyDown(VK_SPACE)) 
	{
		rigidBody->velocity.y = 0;
	}
	if (InputManager::GetInstance().getKeyUp(VK_DOWN))
	{
		rigidBody->velocity.y = 0;
	}
}

void Ball::handleAim()
{

	if (InputManager::GetInstance().getKeyDown(VK_LBUTTON))
	{
		showLine = true;

		Vector2 pos = { gameObject->transform.position.x + m_centerScreen.x, gameObject->transform.position.y + m_centerScreen.y };

		m_renderLine.startPoint = Vector2(pos.x, pos.y);

	}
	if (InputManager::GetInstance().getKey(VK_LBUTTON))
	{

		Vector2 mousePosition = InputManager::GetInstance().getMousePosition();


		Vector2 currentPosition = m_renderLine.startPoint - mousePosition;

		m_renderLine.endPoint = m_renderLine.startPoint - currentPosition;

	}

	if (InputManager::GetInstance().getKeyUp(VK_LBUTTON))
	{
		showLine = false;
	}
}

void Ball::renderLine()
{
	if (showLine)
	{
		/*std::string getLineStartX = std::to_string(m_renderLine.startPoint.x);
		std::string getLineStartY = std::to_string(m_renderLine.startPoint.y);
		std::string getLineEndtX = std::to_string(m_renderLine.endPoint.x);
		std::string getLineEndtY = std::to_string(m_renderLine.endPoint.y);
		std::string total = getLineStartX + " " + getLineStartY + " " + getLineEndtX + " " + getLineEndtY;
		App::Print(100, 100, total.c_str(), 1, 1, 1);*/
		App::DrawLine(m_renderLine.startPoint.x, m_renderLine.startPoint.y, m_renderLine.endPoint.x, m_renderLine.endPoint.y, 1, 0, 0);
	}



}
