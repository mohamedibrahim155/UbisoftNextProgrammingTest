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
}

void BallController::initialize(RigidBody* ballphysics, SpriteRenderer* ballSprite, CircleCollider* collider)
{
	this->pRigidBody = ballphysics;
	this->pSprite = ballSprite;
	this->pCollider = collider;

	pGameObject = pBall->getEntity();

	m_initalPosition = pGameObject->transform.position;
}

void BallController::handleAim()
{
	if (m_state != BallState::IDLE && m_state != BallState::AIMING) return;

	if (InputManager::GetInstance().getKeyDown(VK_LBUTTON))
	{
		m_state = BallState::AIMING;
		Vector2 pos = { pGameObject->transform.position.x + m_centerScreen.x, pGameObject->transform.position.y + m_centerScreen.y };

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
		m_renderLine = { Vector2::Zero(), Vector2::Zero() };
		shootBall(m_aimDirection);
		m_state = BallState::SHOOTING;
	}
}

void BallController::restBall()
{
	if (m_state == BallState::SHOOTING && !isBallMoving()) 
	{

		pRigidBody->velocity = Vector2::Zero();
		m_state = BallState::IDLE;
		setAimState(true);
	}
}

void BallController::resetBall()
{
	pGameObject->transform.position = m_initalPosition;
	pRigidBody->velocity = Vector2::Zero();
	setAimState(true);
}

void BallController::renderTrajectory()
{
	if (m_state != BallState::AIMING) return;

	Vector2 trajectoryStart = m_renderLine.startPoint;

	float length = m_aimDirection.Magnitude();
	float value = length > m_maxLineThreshold ? m_maxLineThreshold : length;

	Vector2 trajectoryDirection = m_aimDirection.Normalize() * value*0.5f;

	// Render trajectory points
	for (float t = 0; t < 2.0f; t += 0.2f)
	{ // Simulate for 2 seconds
		Vector2 position = trajectoryStart - trajectoryDirection * t;
		Debug::DrawCircle(position.x, position.y, 3, 10 , Vector3::One()); // Draw small dots
	}
}

void BallController::shootBall(Vector2 direction)
{
	if (direction.Magnitude() <= 0.01f) return; // Prevent shooting when no direction

	float bounceSpeed = calculateBounceSpeed(direction);

	pRigidBody->velocity += direction.Normalize() * bounceSpeed;

	m_canAim = false;
	
}



bool BallController::isBallMoving()
{
	return pRigidBody->velocity.Magnitude() > 20;
}

bool BallController::cursorInsideRadius()
{

	Vector2 mousePosition = InputManager::GetInstance().getMousePosition();

	Vector2 center = pCollider->getCircle().centre;
	float radius = pCollider->getCircle().radius;

	Vector2 diff = center - mousePosition;

	float dot = diff.x * diff.x + diff.y * diff.y;


	if (dot < m_ballRadius * m_ballRadius)
	{
		return true;
	}

	return false;
}

bool BallController::canAim()
{
	return m_canAim;
}



void BallController::setAimState(bool canAim)
{
	m_canAim = canAim;
}

SLine& BallController::getLineRenderer()
{
	return m_renderLine;
}

float BallController::calculateBounceSpeed(Vector2 aimDir)
{
	float length = aimDir.Magnitude();

	float percentage = length / m_maxLineThreshold;

	float speed = percentage * m_bounceSpeed;

	return speed;
}