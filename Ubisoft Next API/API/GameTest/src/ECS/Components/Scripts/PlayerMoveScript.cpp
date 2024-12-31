#include "stdafx.h"
#include "PlayerMoveScript.h"
#include "../src/ECS/Entity.h"
#include "../App/app.h"
#include "../src/ECS/EntityManager.h"
PlayerMoveScript::PlayerMoveScript() : ScriptComponentBase()
{
}

PlayerMoveScript::~PlayerMoveScript()
{
}

void PlayerMoveScript::start()
{
	
	//gameObject->AddComponent(new SpriteSheetRenderer(ASSET_PATH + "IdleBLUE- 150ms - 32x32.png",6,1));

	spriteSheet = (SpriteSheetRenderer*)gameObject->GetComponent(ComponentType::RENDER_COMPONENT);


	const float speed = 1.0f / 15.0f;
	spriteSheet->createAnimation(0, speed, { 0,1,2,3,4,5,6 });
}

void PlayerMoveScript::updateComponent()
{
	//if (gameObject->isDestroyed) return;
	//Vector3 pos = gameObject->transform.position;

	//pos.x += 1.0f;

	//float rotation = gameObject->transform.rotation;

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
	{
		
		//gameObject->Destroy();


		Entity* entity = gameObject->manager->getEntityByID(1);

		if (entity)
		{
			entity->Destroy();
		}
		

			//spriteSheet->SetAnimation(0);


		
	}
	else
	{
		//spriteSheet->SetAnimation(-1);
	}


	//gameObject->transform.position = (pos);
	

}

void PlayerMoveScript::render()
{
}

PlayerMoveScript* PlayerMoveScript::clone() const
{
	return new PlayerMoveScript();
}
