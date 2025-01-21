///////////////////////////////////////////////////////////////////////////////
// Filename: MainMenu.cpp
// Scene has loads the assets and functionaly for the main menu
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

#pragma once
#include "../BaseLevel.h"
#include "../src/Factory/GameObjectFactory.h"


//-----------------------------------------------------------------------------
// MainMenu inherited from BaseLevel
//-----------------------------------------------------------------------------
class MainMenu  : public BaseLevel
{
public:
	MainMenu();
	~MainMenu() override;
	// Inherited via BaseLevel
	void start() override;
	void cleanScene() override;
	bool isLevelCompleted() override;
private:

	GameObjectFactory* factory;

	const std::string TITLE_UI_PATH = ASSET_PATH + "\\Background\\Title.png";
	const std::string PLAY_BUTTON_UI_PATH = ASSET_PATH + "\\UI\\Button\\Play.png";
	const std::string CONTROLS_BUTTON_UI_PATH = ASSET_PATH + "\\UI\\Button\\Controls.png";
	const std::string CREDITS_BUTTON_UI_PATH = ASSET_PATH + "\\UI\\Button\\Credits.png";
	const std::string ON_HOVER_SFX = ASSET_PATH + "\\Sounds\\SFX\\UI" + "\\001_Hover_01.wav";
	const std::string ON_CLICK_SFX = ASSET_PATH + "\\Sounds\\SFX\\UI" + "\\013_Confirm_03.wav";
	const std::string BACGROUND_MUSIC = ASSET_PATH + "\\Sounds\\BGM\\joy.mp3";

	void createBackground();
	void createButtons();

	void stopPlaying(const std::string& fileName);
	void playOnce(const std::string& fileName);
	void playBackgroundMusic(const std::string& fileName);

	

	
};

