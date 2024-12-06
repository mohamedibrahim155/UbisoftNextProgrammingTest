#include "stdafx.h"
#include "SceneOne.h"
#include "../src/Utils/Utils.h"
#include "App/app.h"
CSceneOne::CSceneOne(eScene name) : CBaseScene(name)
{
	sprite = App::CreateSprite(".\\TestData\\IdleBLUE- 150ms - 32x32.png", 6, 1);
	sprite->CreateAnimation(2, 1.0f / 15.0f, { 0,1,2,3,4,5,6 });

	gameobject = new CGameObject(sprite);

	gameobject->OnDestroyedEvent.Subscribe("Destroyed", [this]()
		{
		   CSimpleSprite*	sprite1 = App::CreateSprite(".\\TestData\\IdleBLUE- 150ms - 32x32.png", 6, 1);
		   sprite1->CreateAnimation(2, 1.5f, { 0,1,2,3,4,5,6 });
			CGameObject* NewObject = new CGameObject(sprite1);

			NewObject->SetPosition(APP_VIRTUAL_WIDTH /2, APP_VIRTUAL_HEIGHT / 2);

		});
}


void CSceneOne::Start()
{
	gameobject->SetPosition(Random::RandomRange(0, APP_VIRTUAL_WIDTH) , Random::RandomRange(0, APP_VIRTUAL_HEIGHT));
}

float timer = 5.0f;
float elapsedTime = 0;

void CSceneOne::Update()
{

	if (App::GetController().CheckButton(APP_PAD_EMUL_LEFT_THUMB_LEFT,true))
	{
		ChangeScene(SCENE_2);
	}



	if (elapsedTime >= timer)
	{
		gameobject->SetPosition(Random::RandomRange(0, APP_VIRTUAL_WIDTH), Random::RandomRange(0, APP_VIRTUAL_HEIGHT));
		elapsedTime = 0;
	}
	else
	{
		elapsedTime += Timer::GetInstance().deltaTime;
	}

	gameobject->GetSprite()->SetAnimation(2);
	
}




void CSceneOne::Render()
{

}

void CSceneOne::CleanScene()
{
	gameobject->Clean();
}
