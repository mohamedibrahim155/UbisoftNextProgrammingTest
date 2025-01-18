///////////////////////////////////////////////////////////////////////////////
// Filename: Level1.cpp
// Scene that load the Level 1 assets
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#pragma once
#include "../BaseLevel.h"
//-----------------------------------------------------------------------------
// Level1 inherited from BaseLevel
//-----------------------------------------------------------------------------

class Level1 : public BaseLevel
{
public:
	Level1();

	~Level1() override = default;
	// Inherited via CBaseScene
	void initialize() override;
	void cleanScene() override;
	bool isLevelCompleted() override;
private:

	// Determines the center of window screen
	Vector2 m_centerScreen;
	
	// method to create invisble walls around
	void createWalls();

	void updateTimer();

	float timer;
	bool levelOneCompleted = false;
	


};

