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
#include "../src/InputManager/InputManager.h"



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
void MainMenu::start()
{

	// Create background and buttons
	createBackground();
	createButtons();

	playBackgroundMusic(BACGROUND_MUSIC);
}

void MainMenu::cleanScene()
{
	systemManager->cleanSystem();
	entityManager->clean();
}

// Method to create background asset
void MainMenu::createBackground()
{
	factory->createBackground();
	factory->createBackgroundWhiteBorder();
    factory->createSpriteObject(TITLE_UI_PATH, Vector2::Zero(), -2);
}


// Method to create buttons
void MainMenu::createButtons()
{

     //Creates play button entity and position accordingly	
#pragma region PlayButton


	const Vector3  buttonTextColor(0.902, 0.451, 0);

	Entity* playButtonGameObject = factory->createButton(PLAY_BUTTON_UI_PATH);
	ButtonRenderer* playButton =	(ButtonRenderer*)playButtonGameObject->getComponent(eComponentType::RENDER_COMPONENT);
	


	
	playButton->addListenersOnButtonHover([this]()
		{
			playOnce(ON_HOVER_SFX);
			
		
		});
	playButton->addListenersOnButtonHoverExit([this]()
		{
			stopPlaying(ON_HOVER_SFX);

		});
	playButton->addListenersOnButtonPress([this]()
		{
		
			playOnce(ON_CLICK_SFX);
			loadScene(LEVEL_1);
		});

	playButtonGameObject->transform.position = Vector3(0, 55, 0);
#pragma endregion

	//Creates ControlsButton  entity and position accordingly	
#pragma region ControlsButton

	Entity* controlButtonGameObject = factory->createButton(CONTROLS_BUTTON_UI_PATH);

	ButtonRenderer* controlButton = (ButtonRenderer*)controlButtonGameObject->getComponent(eComponentType::RENDER_COMPONENT);


	// Events OnButton hover,Click and HoverExit
	controlButton->addListenersOnButtonHover([this]()
		{
			playOnce(ON_HOVER_SFX);
		});

	controlButton->addListenersOnButtonPress([this]()
		{
			playOnce(ON_CLICK_SFX);
			loadScene(CONTROLS);
		});

	controlButton->addListenersOnButtonHoverExit([this]()
		{
			stopPlaying(ON_HOVER_SFX);
			
		});

	//Update position and scale
	controlButtonGameObject->transform.position = Vector3(0, -70, 0);
#pragma endregion



}

//Checks and stops the sound if it is playing
void MainMenu::stopPlaying(const std::string& fileName)
{
	if (App::IsSoundPlaying(fileName.c_str()))
	{
		App::StopSound(fileName.c_str());
	}
}

//Plays the sound once
void MainMenu::playOnce(const std::string& fileName)
{
	App::PlaySound(fileName.c_str(), false);
}

// Plays Background music
void MainMenu::playBackgroundMusic(const std::string& fileName)
{
	if (App::IsSoundPlaying(fileName.c_str())) return;

	App::PlaySound(fileName.c_str(), true);
}

bool MainMenu::isLevelCompleted()
{
	return false;
}




