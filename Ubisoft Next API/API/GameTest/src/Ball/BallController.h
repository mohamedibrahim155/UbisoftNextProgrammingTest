
///////////////////////////////////////////////////////////////////////////////
// Filename: BallController.h
// Controls the ball movement and behavior
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#pragma once
#include "Ball.h"
#include "../Pool/Entity/EntityPool.h"
#include "EColorType.h"
#include "../src/Events/Event.h"


//-----------------------------------------------------------------------------
// States of Ball
//-----------------------------------------------------------------------------
enum class eBallState
{
	IDLE,
	AIMING,
	SHOOTING
};

class BallController
{

public:

	BallController(BallComponent* ballComponent);

	~BallController();

	//Initialise
	void init(EntityManager* entityManager);
	void initPool();

	//Updates the Aim direction
	void updateAim();

	// renders projectile line to screen
	void renderAimLine();

	//resets
	void reset();
	void resetPoolEntites();

	//Setter
	void setColorType(eColorType type);

	//Getters
	bool isWithinCursorRange();
	std::string getCurrentState();
	eColorType getColor() const { return m_type; };

private:

	bool isGameOver = false;

	const float m_maxLineThreshold = 100;
	const float m_bounceSpeed = 1000;
	const float m_cursoeRadius = 250;
	const float m_stoppingFactor = 35;

	const std::string BALL_SPRITE_PATH = ASSET_PATH + "\\Default\\circle_256.png";

	eBallState m_state = eBallState::IDLE;
	eColorType m_type = eColorType::WHITE;

	Vector2 m_aimDirection;
	Vector3 m_initalPosition;

	//center of window
	Vector2 m_centerScreen = { APP_VIRTUAL_WIDTH / 2 ,APP_VIRTUAL_HEIGHT / 2 };

	// render Line
	SLine m_projectileLine;

	// references
	BallComponent* pBall;
	Entity* pGameObject;
	RigidBody* pRigidBody;
	SpriteRenderer* pSprite;
	CircleCollider* pCollider;
	ParticleComponent* pParticle;
	EntityManager* pEntityManager;

	EntityPool* pEntityPool;

	// checks if ball's in motion
	bool isMoving();

	// calculates bounce speed based on drag length
	float calculateBounceVelocity(Vector2 aimDir);

	//states
	void onIdleState();
	void onAimState();
	void onShootState();
	void setCurrentState(eBallState nextState);

	// collisions
	void subscribeEvents();
	void onCollisionEnter(Collider* collider);

	// updates sprite color based on type
	void updateSpriteColor(eColorType type);

	//method checks the gameOver condition
	void checkGameOver();

	// shoot the ball on a given direction
	void launchBall(Vector2 direction);

	// force stop ball
	void haltBall();
};

