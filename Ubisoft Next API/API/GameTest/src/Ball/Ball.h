#pragma once
#include "../src/ECS/Components/Scripts/ScriptComponent.h"
#include "../src/ECS/Components/Collider/CircleCollider.h"
#include "../src/ECS/Components/Rigidbody/RigidBody.h"
#include "../src/ECS/Components/Particle/ParticleComponent.h"

class BallController;

class Ball : public BaseScriptComponent
{
public:
	Ball(EntityManager* entityManager);
	~Ball() override = default;
     void start() override;
     void updateComponent() override;
     void render(bool isDebugVisible) override;
     void cleanUp() override;

	 void setSpawnPosition(const float& x, const float& y);
private:

	const std::string BALL_TEXTURE_PATH = ASSET_PATH + "\\Ball\\ball_red_small.png";

	Vector3 m_spawnPosition;

	// references
	RigidBody* rigidBody;
	SpriteRenderer* ballSprite;
	Collider* circleCollider;
	ParticleComponent* particleComponent;

	BallController* controller;
	EntityManager* entityManager;

	void createBall();
};

