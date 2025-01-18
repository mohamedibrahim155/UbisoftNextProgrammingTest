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
	restBall();
	updateInput();
}

void Ball::render(bool isDebugVisible)
{
	renderLine();
}

void Ball::cleanUp()
{
}

float Ball::calculateBounceSpeed(Vector2 aimDir)
{
	float length = aimDir.Magnitude();

	float percentage = length / m_maxLineThreshold;

	float speed = percentage * m_bounceSpeed;

	return speed;
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
	if (!m_canAim) return;

	if (InputManager::GetInstance().getKeyDown(VK_LBUTTON))
	{
		m_showLine = true;

		Vector2 pos = { gameObject->transform.position.x + m_centerScreen.x, gameObject->transform.position.y + m_centerScreen.y };

		m_renderLine.startPoint = Vector2(pos.x, pos.y);

	}
	if (InputManager::GetInstance().getKey(VK_LBUTTON))
	{

		Vector2 mousePosition = InputManager::GetInstance().getMousePosition();


		Vector2 currentPosition = m_renderLine.startPoint - mousePosition;


		float length = currentPosition.Magnitude();

		currentPosition = (length > m_maxLineThreshold) ? 
			currentPosition.Normalize() * m_maxLineThreshold : currentPosition.Normalize() * length;

		m_renderLine.endPoint = m_renderLine.startPoint - currentPosition;

		m_aimDirection = m_renderLine.startPoint - m_renderLine.endPoint;
	}

	if (InputManager::GetInstance().getKeyUp(VK_LBUTTON))
	{
		m_showLine = false;
		m_canAim = false;
		OnBallRelease();
	}
}

void Ball::OnBallRelease()
{
	float bounceSpeed = calculateBounceSpeed(m_aimDirection);

	rigidBody->velocity +=  m_aimDirection.Normalize() * bounceSpeed;
}

void Ball::renderLine()
{
	if (m_showLine)
	{
		App::DrawLine(m_renderLine.startPoint.x, m_renderLine.startPoint.y, m_renderLine.endPoint.x, m_renderLine.endPoint.y, 1, 0, 0);
	}

	std::string total = rigidBody ? std::to_string(rigidBody->velocity.x) + " " + std::to_string(rigidBody->velocity.y) : " ";
	App::Print(100, 100, total.c_str(), 1, 1, 1);
	
}

void Ball::restBall()
{
	if (!m_canAim)
	{
		if (rigidBody->velocity.Magnitude() < 20.0f)
		{
			rigidBody->velocity = Vector2::Zero();
			m_canAim = true;

		}
	}
	
}
