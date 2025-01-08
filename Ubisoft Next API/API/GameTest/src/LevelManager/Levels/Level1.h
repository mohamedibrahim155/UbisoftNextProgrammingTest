#pragma once
#include "../BaseLevel.h"
class Level1 : public BaseLevel
{
public:
	Level1() : BaseLevel(LEVEL_1) {};

	~Level1() override = default;
	// Inherited via CBaseScene
	void initialize() override;
	void cleanScene() override;
	
};

