#pragma once
#include "../BaseLevel.h"
class Level2 :
    public BaseLevel
{
public:
	Level2() : BaseLevel(LEVEL_2) {};

	~Level2() override = default;
	// Inherited via CBaseScene
	void initialize() override;
	void cleanScene() override;
	bool isLevelCompleted() override;
};

