#pragma once
#include "../src/ECS/Components/Scripts/ScriptComponent.h"
#include "../src/ECS/Components/Collider/CircleCollider.h"
#include "../src/ECS/Components/Rigidbody/RigidBody.h"
#include "../src/ECS/Components/Renders/SpriteRenderer.h"
#include "../src/ECS/Components/Particle/ParticleComponent.h"
class GoalPost : public BaseScriptComponent

{

public:
	GoalPost(const Vector2& spawnPosition);
	~GoalPost() override = default;
	 void start() override;
	 void updateComponent() override;
	 void render(bool isDebugVisible) override {};
	 void cleanUp() override {};
private:

	const std::string SPRITE_PATH = ASSET_PATH + "\\Ball\\hole_large.png";
	const std::string DEFAULT_CIRCLE_PATH = ASSET_PATH + "\\Default\\circle-512.png";

	bool m_hasReached = false;
	float m_delayTime = 1;
	
	Vector2 m_spawnPosition;

	CircleCollider* pCircleCollider;
	RigidBody* pRigidbody;
	SpriteRenderer* pSprite;
	ParticleComponent* pParticle;
	

	void createGoalHole();
	void subscribeOnTrigger();
	void onTriggerEnter(Collider* collider);

	void targetReached();
	void checkGoalReached();
	void reset();


};

