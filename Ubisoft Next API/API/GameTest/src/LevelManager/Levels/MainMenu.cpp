///////////////////////////////////////////////////////////////////////////////
// Filename: MainMenu.cpp
// Scene has loads the assets and functionaly for the main menu
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "MainMenu.h"
#include "../src/ECS/Systems//Render/RenderSystem.h"
#include "../src/ECS/Systems//CustomScripts/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/Movement/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"



MainMenu::MainMenu(): BaseLevel(MAINMENU) 
{
	// Factory to create different types of game objects
	factory = new GameObjectFactory(entityManager);
}
MainMenu::~MainMenu()
{
	if (factory)
	{
		delete factory;
	}

}
void MainMenu::initialize()
{

	// Create background and buttons
	createBackground();
	createButtons();
}

void MainMenu::cleanScene()
{
	systemManager->cleanSystem();
}

// Method to create background asset
void MainMenu::createBackground()
{
	std::string UIFilePath = ASSET_PATH + "\\UI\\Background\\";

	
	Entity* background = factory->createSpriteObject(UIFilePath  + "background_0.png",Vector2::Zero(), -1);
	background->transform.scale = Vector2(5,5);

	// TODO: Add background music
	//std::string bgMusicAssetPath;
	//PlayBackgroundMusic(bgMusicAssetPath)

}


// Method to create buttons
void MainMenu::createButtons()
{

     //Creates play button entity and position accordingly	
#pragma region PlayButton


	const Vector3  buttonTextColor(0.902, 0.451, 0);

	Entity* playButtonGameObject = factory->createButtonWithText(UIFilePath + "b_1.png", "Play", buttonTextColor);

	ButtonRenderer* playButton =	(ButtonRenderer*)playButtonGameObject->getComponent(eComponentType::RENDER_COMPONENT);
	playButton->getTextComponent()->setFont(BITMAP_TIMES_ROMAN_24);
	playButton->getTextComponent()->setOffset(Vector2(-20, -5));
	


	
	playButton->addListenersOnButtonHover([this]()
		{
			PlayOnce(OnhoverSFX);
		});
	playButton->addListenersOnButtonHoverExit([this]()
		{
			StopPlaying(OnhoverSFX);
		});
	playButton->addListenersOnButtonPress([this]()
		{
		
			PlayOnce(OnclickSFX);
		});

	playButtonGameObject->transform.position = Vector3(0, 50, 0);
	playButtonGameObject->transform.scale = Vector2(0.2f, 0.2f);
#pragma endregion

	//Creates ControlsButton  entity and position accordingly	
#pragma region ControlsButton

	Entity* optionMenuGameobject = factory->createButtonWithText(UIFilePath + "b_1.png", "Controls", buttonTextColor);

	ButtonRenderer* controlButton = (ButtonRenderer*)optionMenuGameobject->getComponent(eComponentType::RENDER_COMPONENT);
	controlButton->getTextComponent()->setFont(BITMAP_TIMES_ROMAN_24);
	controlButton->getTextComponent()->setOffset(Vector2(-40, -5));



	// Events OnButton hover,Click and HoverExit
	controlButton->addListenersOnButtonHover([this]()
		{
			PlayOnce(OnhoverSFX);
		});

	controlButton->addListenersOnButtonPress([this]()
		{
			PlayOnce(OnclickSFX);
		});

	controlButton->addListenersOnButtonHoverExit([this]()
		{
			StopPlaying(OnhoverSFX);
			
		});

	//Update position and scale
	optionMenuGameobject->transform.position = Vector3(0, -50, 0);
	optionMenuGameobject->transform.scale = Vector2(0.2f, 0.2f);
#pragma endregion

	//Creates Credit button  entity and position accordingly	
#pragma region CreditButton

	Entity* creditGameObject = factory->createButtonWithText(UIFilePath + "b_1.png", "Credits", buttonTextColor);

	ButtonRenderer* creditButton = (ButtonRenderer*)creditGameObject->getComponent(eComponentType::RENDER_COMPONENT);
	creditButton->getTextComponent()->setFont(BITMAP_TIMES_ROMAN_24);
	creditButton->getTextComponent()->setOffset(Vector2(-30, -5));
	

	// Events OnButton hover,Click and HoverExit
	creditButton->addListenersOnButtonHover([this]()
		{
			PlayOnce(OnhoverSFX);
		});

	creditButton->addListenersOnButtonPress([this]()
		{
			PlayOnce(OnclickSFX);
		});

	creditButton->addListenersOnButtonHoverExit([this]()
		{
			StopPlaying(OnhoverSFX);
		});

	
	//Update position and scale
	creditGameObject->transform.position = Vector3(0, -150, 0);
	creditGameObject->transform.scale = Vector2(0.2f, 0.2f);
#pragma endregion

}

//Checks and stops the sound if it is playing
void MainMenu::StopPlaying(const std::string& fileName)
{
	if (App::IsSoundPlaying(fileName.c_str()))
	{
		App::StopSound(fileName.c_str());
	}
}

//Plays the sound once
void MainMenu::PlayOnce(const std::string& fileName)
{
	App::PlaySound(fileName.c_str(), false);
}

// Plays Background music
void MainMenu::PlayBackgroundMusic(const std::string& fileName)
{
}




