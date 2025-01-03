#pragma once
#include "../BaseLevel.h"
class Level1 : public BaseLevel
{
public:
	Level1() : BaseLevel(SCENE_1) {};

	~Level1() override = default;
	// Inherited via CBaseScene
	void Initialize() override;
	void CleanScene() override;
	
};

