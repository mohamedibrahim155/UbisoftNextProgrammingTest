///////////////////////////////////////////////////////////////////////////////
// Filename: Level1.cpp
// Scene that load the Level 1 assets
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#pragma once
#include "../BaseLevel.h"
#include "../src/Factory/GameObjectFactory.h"
#include "../src/Ball/GoalPost.h"
//-----------------------------------------------------------------------------
// Level1 inherited from BaseLevel
//-----------------------------------------------------------------------------

class Level1 : public BaseLevel
{
public:
	Level1();

	~Level1() override;
	// Inherited via CBaseScene
	void start() override;
	void cleanScene() override;
	bool isLevelCompleted() override;
private:

	const std::string LEVEL_ONE_PATH = ASSET_PATH + "\\Background\\LevelOne.png";
	bool levelOneCompleted = false;
	// Determines the center of window screen
	Vector2 m_centerScreen;
	

	GameObjectFactory* factory;
	// method to create invisble walls around
	void createWalls();

	//creates BackgroundImages
	void createBackground();

	void createBlocks();

	
	GoalPost* goalPost;


};

