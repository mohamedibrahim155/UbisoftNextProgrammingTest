#pragma once
#include "Ball.h"
#include "../Pool/Entity/EntityPool.h"

enum class eBallState
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


	bool isInRange();

	//Initialise
	void initialize(EntityManager* entityManager);
	void initializePool();
	void handleAim();

	void reset();
	void resetPoolEntites();
	void renderTrajectory();

	std::string getState();

private:


	float m_maxLineThreshold = 100;
	float m_bounceSpeed = 500;
	float m_cursoeRadius = 250;
	float m_stoppingFactor = 35;

	const std::string CIRCLE_PATH = ASSET_PATH + "\\Default\\circle_256.png";
	eBallState m_state = eBallState::IDLE;

	Vector2 m_aimDirection;
	Vector3 m_initalPosition;
	Vector2 m_centerScreen = { APP_VIRTUAL_WIDTH / 2 ,APP_VIRTUAL_HEIGHT / 2 };

	// rendersLine
	SLine m_projectileLine;

	// references
	Ball* pBall;
	Entity* pGameObject;
	RigidBody* pRigidBody;
	SpriteRenderer* pSprite;
	CircleCollider* pCollider;
	ParticleComponent* pParticle;
	EntityManager* pEntityManager;

	EntityPool* pEntityPool;


	bool isMoving();
	float calculateBounceSpeed(Vector2 aimDir);

	void subscribeCollisionEvent();
	void shootBall(Vector2 direction);
	void stopBall();

	//states
	void aimState();
	void shootState();
	void idleState();
	void setState(eBallState nextState);

	void onCollisionStay(Collider* collider);
};

