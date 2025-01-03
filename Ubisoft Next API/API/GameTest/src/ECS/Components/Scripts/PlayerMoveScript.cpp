#include "stdafx.h"
#include "PlayerMoveScript.h"
#include "../src/ECS/Entity.h"
#include "../App/app.h"
#include "../src/ECS/EntityManager.h"
#include "../src/Utils/PhysicsUtils.h"
#include "../src/SceneManger/Scenes/Level2.h"
#include "../src/SceneManger/SceneManager.h"
PlayerMoveScript::PlayerMoveScript() : BaseScriptComponent()
{
}

PlayerMoveScript::~PlayerMoveScript()
{
}

void PlayerMoveScript::start()
{
	
	//gameObject->AddComponent(new SpriteSheetRenderer(ASSET_PATH + "IdleBLUE- 150ms - 32x32.png",6,1));

	m_spriteSheet = (SpriteSheetRenderer*)gameObject->getComponent(ComponentType::RENDER_COMPONENT);


	const float speed = 1.0f / 15.0f;
	m_spriteSheet->createAnimation(0, speed, { 0,1,2,3,4,5,6 });
}

void PlayerMoveScript::updateComponent()
{
	//if (gameObject->isDestroyed) return;
	/*Vector3 pos = gameObject->transform.position;

	pos.x += 1.0f;*/

	//float rotation = gameObject->transform.rotation;

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		
		//gameObject->Destroy();


		//Entity* entity = gameObject;

		//Vector3 pos = gameObject->transform.position;

	 //   pos.x += 10.0f;

		//if (entity)
		//{
		//	entity->transform.position.x+= -1.0f;
		//}
		//


		

			//spriteSheet->SetAnimation(0);

		
		
	}
	else
	{
		//spriteSheet->SetAnimation(-1);
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		LevelManager::GetInstance().ChangeScene(SCENE_2);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		LevelManager::GetInstance().ChangeScene(SCENE_1);
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
