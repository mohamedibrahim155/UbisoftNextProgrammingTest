#pragma once
#include "../src/ECS/Components/Scripts/ScriptComponent.h"
#include "../src/ECS/Components/Renders/SpriteRenderer.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/ECS/Components/Rigidbody/RigidBody.h"
#include "../src/Ball/EColorType.h"


class Block :  public BaseScriptComponent
{
public :

	Block(eColorType type);
	~Block() override = default;
     void start() override;
	 void updateComponent() override ;
	virtual void render(bool isDebugVisible) override {};
	virtual void cleanUp() override {};


	void changeType(eColorType newType);
	void changeSprite(eColorType type);
	void setTriggerState(bool state);
	bool isTrigger();


	eColorType getType() const { return m_type; };
private:
	const std::string BLOCK_TEXTURE_PATH = ASSET_PATH + "\\Block\\Block_256.png";
	
	bool m_collisionTrigger = false;
	eColorType m_type = eColorType::WHITE;

	// references
	BoxCollider* pCollider;
	SpriteRenderer* pSprite;
	RigidBody* pRigidbody;

	void createBlock();
	
};

