#pragma once
#include "../BaseScene.h"
class Level2 :
    public CBaseScene
{
public:
	Level2() : CBaseScene(SCENE_2) {};

	~Level2() override = default;
	// Inherited via CBaseScene
	void Initialize() override;
	void CleanScene() override;
};

