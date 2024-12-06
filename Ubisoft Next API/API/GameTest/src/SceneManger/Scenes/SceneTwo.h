#pragma once
#include "../BaseScene.h"
class CSceneTwo :  public CBaseScene
{
public:
	CSceneTwo(std::string name);

	 void Start()  override;
	 void Update() override;
	 void Render() override;
	 void CleanScene()  override;

};

