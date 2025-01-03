#pragma once
#include "../BaseScene.h"
class Level1 : public CBaseScene
{
public:
	Level1() : CBaseScene(SCENE_1) {};

	~Level1() override = default;
	// Inherited via CBaseScene
	void Initialize() override;
	void CleanScene() override;
	
};

