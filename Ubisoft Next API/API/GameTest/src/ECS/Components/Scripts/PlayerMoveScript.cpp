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
	
	//gameObject->AddComponent(new SpriteSheetRenderer(ASSET_PATH + "IdleBLUE- 150ms - 32x32.png",6,1));

	spriteSheet = (SpriteSheetRenderer*)gameObject->GetComponent(ComponentType::RENDER_COMPONENT);


	const float speed = 1.0f / 15.0f;
	spriteSheet->CreateAnimation(0, speed, { 0,1,2,3,4,5,6 });
}

void PlayerMoveScript::UpdateComponent()
{
	//if (gameObject->isDestroyed) return;
	//Vector3 pos = gameObject->transform.position;

	//pos.x += 1.0f;

	//float rotation = gameObject->transform.rotation;

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		
		gameObject->Destroy();
			//spriteSheet->SetAnimation(0);


		
	}
	else
	{
		//spriteSheet->SetAnimation(-1);
	}


	//gameObject->transform.position = (pos);
	

}

void PlayerMoveScript::Render()
{
}

PlayerMoveScript* PlayerMoveScript::Clone() const
{
	return new PlayerMoveScript();
}
