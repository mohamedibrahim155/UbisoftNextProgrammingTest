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
	void initialize() override;
	void cleanScene() override;
	bool isLevelCompleted() override;
private:

	bool isMainMenuLevelCompleted = false;
	GameObjectFactory* factory;

	const std::string BUTTON_UI_PATH = ASSET_PATH + "\\UI\\Basic\\";
	const std::string BACKGROUND_PATH = ASSET_PATH + "\\UI\\Background\\";
	const std::string ON_HOVER_SFX = ASSET_PATH + "\\Sounds\\SFX\\UI" + "\\001_Hover_01.wav";
	const std::string ON_CLICK_SFX = ASSET_PATH + "\\Sounds\\SFX\\UI" + "\\013_Confirm_03.wav";

	void createBackground();
	void createButtons();

	void stopPlaying(const std::string& fileName);
	void playOnce(const std::string& fileName);
	void playBackgroundMusic(const std::string& fileName);
	void loadScene(eScene scene);

	

	
};

