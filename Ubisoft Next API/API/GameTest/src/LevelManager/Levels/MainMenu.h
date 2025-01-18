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

private:

	GameObjectFactory* factory;

	const std::string UIFilePath = ASSET_PATH + "\\UI\\Basic\\";
	const std::string OnhoverSFX = ASSET_PATH + "\\Sounds\\SFX\\UI" + "\\001_Hover_01.wav";
	const std::string OnclickSFX = ASSET_PATH + "\\Sounds\\SFX\\UI" + "\\013_Confirm_03.wav";

	void createBackground();
	void createButtons();

	void stopPlaying(const std::string& fileName);
	void playOnce(const std::string& fileName);
	void playBackgroundMusic(const std::string& fileName);
	void loadScene(eScene scene);
};

