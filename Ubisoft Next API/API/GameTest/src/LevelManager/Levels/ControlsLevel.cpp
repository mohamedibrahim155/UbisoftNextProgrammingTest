///////////////////////////////////////////////////////////////////////////////
// Filename: ControlLevel.cpp
// Scene has loads the assets and functionaly for the main menu
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "ControlsLevel.h"

#include "../src/ECS/Systems//Render/RenderSystem.h"
#include "../src/ECS/Systems//CustomScripts/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/Movement/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"
#include "../src/InputManager/InputManager.h"



#include "../src/ECS/Systems//Render/RenderSystem.h"
#include "../src/ECS/Systems//CustomScripts/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/Movement/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"
#include "../src/InputManager/InputManager.h"



ControlsLevel::ControlsLevel(): BaseLevel(CONTROLS)
{
	// Factory to create different types of game objects
	factory = new GameObjectFactory(entityManager);
}
ControlsLevel::~ControlsLevel()
{
	if (factory)
	{
		delete factory;
	}

}
void ControlsLevel::start()
{

	// Create background and buttons
	createBackground();
	createButtons();
}

void ControlsLevel::cleanScene()
{
	systemManager->cleanSystem();
	entityManager->clean();
}

// Method to create background asset
void ControlsLevel::createBackground()
{
	factory->createBackground();
	factory->createBackgroundWhiteBorder();
	factory->createSpriteObject(CONTROLS_UI_PATH, Vector2::Zero(), -2);
}


// Method to create buttons
void ControlsLevel::createButtons()
{

     //Creates Menu entity and position accordingly	
#pragma region Menu


	const Vector3  buttonTextColor(0.902, 0.451, 0);

	Entity* menuButtonGameObject = factory->createButton(MENU_BUTON_UI_PATH);
	ButtonRenderer* menuButton =	(ButtonRenderer*)menuButtonGameObject->getComponent(eComponentType::RENDER_COMPONENT);
	


	
	menuButton->addListenersOnButtonHover([this]()
		{
			playOnce(ON_HOVER_SFX);
			
		
		});
	menuButton->addListenersOnButtonHoverExit([this]()
		{
			stopPlaying(ON_HOVER_SFX);

		});
	menuButton->addListenersOnButtonPress([this]()
		{
		
			playOnce(ON_CLICK_SFX);
			loadScene(MAINMENU);
		});

	menuButtonGameObject->transform.position = Vector3(0, -300, 0);

#pragma endregion

}

//Checks and stops the sound if it is playing
void ControlsLevel::stopPlaying(const std::string& fileName)
{
	if (App::IsSoundPlaying(fileName.c_str()))
	{
		App::StopSound(fileName.c_str());
	}
}

//Plays the sound once
void ControlsLevel::playOnce(const std::string& fileName)
{
	App::PlaySound(fileName.c_str(), false);
}

// Plays Background music
void ControlsLevel::playBackgroundMusic(const std::string& fileName)
{
}

bool ControlsLevel::isLevelCompleted()
{
	return false;
}




