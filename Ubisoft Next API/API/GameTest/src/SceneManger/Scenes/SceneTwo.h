#pragma once
#include "../BaseScene.h"
class CSceneTwo :  public CBaseScene
{
public:
	CSceneTwo(std::string name);

	 void StartScene()  override;
	 void UpdateScene() override;
	 void RenderScene() override;
	 void CleanScene()  override;

};

