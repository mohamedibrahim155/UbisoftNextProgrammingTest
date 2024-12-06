#pragma once
#include "../BaseScene.h"
#include "../src/Entities/GameObject/GameObject.h"
#include "../App/app.h"
class CSceneOne : public CBaseScene
{

public:
	CSceneOne(std::string name);
	 void Start()  override;
	 void Update() override;
	 void Render() override;
	 void CleanScene()  override;

private:
	CSimpleSprite* sprite;

	CGameObject* gameobject;

};

