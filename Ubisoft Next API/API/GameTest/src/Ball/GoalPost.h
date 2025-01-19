#pragma once
#include "../src/ECS/Components/Scripts/ScriptComponent.h"
#include "../src/ECS/Components/Collider/CircleCollider.h"
#include "../src/ECS/Components/Rigidbody/RigidBody.h"
#include "../src/ECS/Components/Renders/SpriteRenderer.h"
class GoalPost : public BaseScriptComponent

{

public:
	GoalPost(const Vector2& spawnPosition);
	~GoalPost() override = default;
	 void start() override;
	 void updateComponent() override;
	 void render(bool isDebugVisible) override {};
	 void cleanUp() override {};

	 bool hasTargetReached();
private:

	bool hasReached = false;
	const std::string SPRITE_PATH = ASSET_PATH + "\\Ball\\hole_large.png";

	Vector2 m_spawnPosition;

	CircleCollider* pCircleCollider;
	RigidBody* pRigidbody;
	SpriteRenderer* pSprite;
	

	void createGoalHole();
	void subscribeOnTrigger();
	void onTrigger(Collider* collider);
	void targetReached();

};

