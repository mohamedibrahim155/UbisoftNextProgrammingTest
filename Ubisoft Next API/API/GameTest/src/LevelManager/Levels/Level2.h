///////////////////////////////////////////////////////////////////////////////
// Filename: Level1.cpp
// Scene that load the Level 2 assets
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#pragma once
#include "../BaseLevel.h"
#include "../src/Factory/GameObjectFactory.h"
#include "../src/Ball/GoalPost.h"
//-----------------------------------------------------------------------------
// Level2 inherited from BaseLevel
class Level2 :
    public BaseLevel
{
public:
	Level2() ;

	~Level2() override;
	// Inherited via CBaseScene
	void start() override;
	void cleanScene() override;
	bool isLevelCompleted() override;

private:
	const std::string LEVEL_ONE_PATH = ASSET_PATH + "\\Background\\LevelOne.png";
	const std::string BLOCK_1_PATH = ASSET_PATH + "\\Block\\Level 1\\Block_1.png";
	const std::string BLOCK_2_PATH = ASSET_PATH + "\\Block\\Level 1\\Block_2.png";
	const std::string BLOCK_3_PATH = ASSET_PATH + "\\Block\\Level 1\\Block_3.png";
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

