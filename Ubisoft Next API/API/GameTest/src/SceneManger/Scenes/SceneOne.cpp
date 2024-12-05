#include "stdafx.h"
#include "SceneOne.h"

CSceneOne::CSceneOne(std::string name) : CBaseScene(name)
{
	sprite = App::CreateSprite(".\\TestData\\IdleBLUE- 150ms - 32x32.png", 6, 1);
	sprite->CreateAnimation(2, 1.5f, { 0,1,2,3,4,5,6 });

	gameobject = new CGameObject(sprite);

	gameobject->OnDestroyedEvent.Subscribe("Destroyed", [this]()
		{
		   CSimpleSprite*	sprite1 = App::CreateSprite(".\\TestData\\IdleBLUE- 150ms - 32x32.png", 6, 1);
		   sprite1->CreateAnimation(2, 1.5f, { 0,1,2,3,4,5,6 });
			CGameObject* NewObject = new CGameObject(sprite1);

			NewObject->SetPosition(APP_VIRTUAL_WIDTH /2, APP_VIRTUAL_HEIGHT / 2);

		});
}


void CSceneOne::StartScene()
{
	gameobject->SetPosition(100.0f, 400.0f);
}

void CSceneOne::UpdateScene()
{

	if (App::GetController().CheckButton(APP_PAD_EMUL_LEFT_THUMB_LEFT,true))
	{
		gameobject->Destroy();
		return;
	}

	
}

void CSceneOne::RenderScene()
{

}

void CSceneOne::CleanScene()
{

	
	sprite = nullptr;
	delete sprite;
	gameobject = nullptr;
	delete gameobject;
}
