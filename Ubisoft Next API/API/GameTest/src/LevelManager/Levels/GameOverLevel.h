///////////////////////////////////////////////////////////////////////////////
// Filename: Gameover.cpp
// Scene has loads the assets and functionaly for the Game over scene
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

#pragma once
#include "../BaseLevel.h"
#include "../src/Factory/GameObjectFactory.h"


//-----------------------------------------------------------------------------
// GameOver inherited from BaseLevel
//-----------------------------------------------------------------------------
class GameOverLevel : public BaseLevel
{
public:
	GameOverLevel();
	~GameOverLevel() override;
	// Inherited via BaseLevel
	void start() override;
	void cleanScene() override;
	bool isLevelCompleted() override;

	void setRetryLevel(eScene retyLevel);
private:

	eScene m_retryLevel = eScene::LEVEL_2;

	GameObjectFactory* factory;

	const std::string RETRY_UI = ASSET_PATH + "\\UI\\Button\\Retry.png";
	const std::string ON_HOVER_SFX = ASSET_PATH + "\\Sounds\\SFX\\UI" + "\\001_Hover_01.wav";
	const std::string ON_CLICK_SFX = ASSET_PATH + "\\Sounds\\SFX\\UI" + "\\013_Confirm_03.wav";

	void createBackground();
	void createButtons();

	void stopPlaying(const std::string& fileName);
	void playOnce(const std::string& fileName);
	void playBackgroundMusic(const std::string& fileName);




};

