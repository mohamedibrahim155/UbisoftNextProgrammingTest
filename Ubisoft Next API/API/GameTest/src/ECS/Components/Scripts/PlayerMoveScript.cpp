#include "stdafx.h"
#include "PlayerMoveScript.h"
#include "../src/ECS/Entity.h"
#include "../../Components/SpriteRenderer.h"
#include "../App/app.h"
#include "../src/ECS/EntityManager.h"
PlayerMoveScript::PlayerMoveScript() : ScriptComponent()
{
}

PlayerMoveScript::~PlayerMoveScript()
{
}

void PlayerMoveScript::Start()
{
	
	//entityRef->AddComponent(new SpriteSheetRenderer(ASSET_PATH + "IdleBLUE- 150ms - 32x32.png",6,1));

	spriteSheet = (SpriteSheetRenderer*)entityRef->GetComponent(ComponentType::RENDER_COMPONENT);


	const float speed = 1.0f / 15.0f;
	spriteSheet->CreateAnimation(0, speed, { 0,1,2,3,4,5,6 });
}

void PlayerMoveScript::UpdateComponent()
{
	Vector3 pos = entityRef->transform.position;

	pos.x += 1.0f;

	entityRef->transform.position = (pos);

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
	{
		
		//entityRef->Destroy();
			spriteSheet->SetAnimation(0);

		
	}
	else
	{
		spriteSheet->SetAnimation(-1);
	}


	

}

void PlayerMoveScript::Render()
{
}

PlayerMoveScript* PlayerMoveScript::Clone() const
{
	return new PlayerMoveScript();
}
