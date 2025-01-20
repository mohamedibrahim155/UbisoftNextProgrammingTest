#pragma once
#include "../src/ECS/Components/Scripts/ScriptComponent.h"
#include "../src/ECS/Components/Collider/CircleCollider.h"
#include "../src/ECS/Components/Rigidbody/RigidBody.h"
#include "../src/ECS/Components/Particle/ParticleComponent.h"
#include "EColorType.h"
class BallController;

class Ball : public BaseScriptComponent
{
public:
	Ball(EntityManager* entityManager, eColorType type);
	~Ball() override = default;
     void start() override;
     void updateComponent() override;
     void render(bool isDebugVisible) override;
     void cleanUp() override;

	 void setSpawnPosition(const float& x, const float& y);

	 BallController* getController() { return controller; }
private:

	const std::string BALL_TEXTURE_PATH = ASSET_PATH + "\\Ball\\ball_red_small2.png";

	eColorType m_intialBallType = eColorType::WHITE;

	Vector3 m_spawnPosition;

	// references
	RigidBody* rigidBody;
	SpriteRenderer* ballSprite;
	Collider* circleCollider;

	BallController* controller;
	EntityManager* entityManager;

	void createBall();
};

