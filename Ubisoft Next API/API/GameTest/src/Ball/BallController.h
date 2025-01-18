#pragma once
#include "Ball.h"



enum class BallState
{
	IDLE,
	AIMING,
	SHOOTING
};
class BallController
{

public:
	BallController(Ball* ballComponent);

	~BallController();



	void initialize(RigidBody* ballphysics, SpriteRenderer* ballSprite, CircleCollider* collider);

	bool canAim();
	bool isBallMoving();
	bool cursorInsideRadius();
	void setAimState(bool canAim);

	void handleAim();
	void restBall();
	void resetBall();
	void renderTrajectory();

	SLine& getLineRenderer();

private:


	bool m_canAim = true;
	bool m_aiming = false;
	bool m_showLine = false;

	float m_maxLineThreshold = 100;
	float m_bounceSpeed = 500;
	float m_ballRadius = 100;

	BallState m_state = BallState::IDLE;

	Vector2 m_aimDirection;
	Vector3 m_initalPosition;
	Vector2 m_centerScreen = { APP_VIRTUAL_WIDTH / 2 ,APP_VIRTUAL_HEIGHT / 2 };


	SLine m_renderLine;

	// references
	Ball* pBall;
	Entity* pGameObject;
	RigidBody* pRigidBody;
	SpriteRenderer* pSprite;
	CircleCollider* pCollider;


	float calculateBounceSpeed(Vector2 aimDir);
	void  shootBall(Vector2 direction);

	

};

