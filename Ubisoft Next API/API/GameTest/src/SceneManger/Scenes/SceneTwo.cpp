#include "stdafx.h"
#include "SceneTwo.h"

CSceneTwo::CSceneTwo(eScene scene) : CBaseScene(scene)
{
	sprite = App::CreateSprite(".\\TestData\\IdleBLUE- 150ms - 32x32.png", 6, 1);
	sprite->CreateAnimation(2, 1.5f, { 0,1,2,3,4,5,6 });

	 gameobject = new CGameObject(sprite);

	gameobject->OnDestroyedEvent.Subscribe("Destroyed", [this]()
		{
			CSimpleSprite* sprite1 = App::CreateSprite(".\\TestData\\IdleBLUE- 150ms - 32x32.png", 6, 1);
			sprite1->CreateAnimation(2, 1.5f, { 0,1,2,3,4,5,6 });
			CGameObject* NewObject = new CGameObject(sprite1);

			NewObject->SetPosition(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

		});
}

void CSceneTwo::Start()
{
	gameobject->SetPosition(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2 + 200);
}

void CSceneTwo::Update()
{
}

void CSceneTwo::Render()
{
}

void CSceneTwo::CleanScene()
{
	sprite = nullptr;
	delete sprite;

	delete gameobject;
}
