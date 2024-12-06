#pragma once
#include "../BaseScene.h"
class CSceneTwo :  public CBaseScene
{
public:
	CSceneTwo(eScene scene);

	 void Start()  override;
	 void Update() override;
	 void Render() override;
	 void CleanScene()  override;

private:
	CSimpleSprite* sprite;
	CGameObject* gameobject;

};

