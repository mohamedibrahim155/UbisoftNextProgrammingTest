#include "stdafx.h"
#include "PlayerMoveScript.h"
#include "../src/ECS/Entity.h"
#include "../../Components/SpriteRenderer.h"
PlayerMoveScript::PlayerMoveScript() : ScriptComponent()
{
}

PlayerMoveScript::~PlayerMoveScript()
{
}

void PlayerMoveScript::Start()
{
}

void PlayerMoveScript::UpdateComponent()
{
	//SpriteRenderer* spriteComp = (SpriteRenderer*)entityRef->GetComponent(ComponentType::RENDER_COMPONENT);

	//CSimpleSprite* sprite = spriteComp->GetSprite();

	//Vector3 position;
	//sprite->GetPosition(position.x, position.y);


	//position.x += 1;
	//entityRef->SetPosition(position);
	// 
	// 
	//SpriteRenderer* spriteComp = (SpriteRenderer*)entityRef->GetComponent(ComponentType::RENDER_COMPONENT);

	Vector3 pos = entityRef->transform.position;

	pos.x += 1;

	entityRef->transform.position = (pos);

}

void PlayerMoveScript::Render()
{
}
