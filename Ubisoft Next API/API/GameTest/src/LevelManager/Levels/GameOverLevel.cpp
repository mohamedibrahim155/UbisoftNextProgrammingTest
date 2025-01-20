
///////////////////////////////////////////////////////////////////////////////
// Filename: GameOverLevel.cpp
// Scene has loads the assets and functionaly for the main menu
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameOverLevel.h"

#include "../src/ECS/Systems//Render/RenderSystem.h"
#include "../src/ECS/Systems//CustomScripts/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/Movement/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"
#include "../src/InputManager/InputManager.h"
//#include "../src/"


GameOverLevel::GameOverLevel() : BaseLevel(GAME_OVER)
{
	// Factory to create different types of game objects
	factory = new GameObjectFactory(entityManager);
}
GameOverLevel::~GameOverLevel()
{
	if (factory)
	{
		delete factory;
	}

}
void GameOverLevel::start()
{

	// Create background and buttons
	createBackground();
	createButtons();
}

void GameOverLevel::cleanScene()
{
	systemManager->cleanSystem();
	entityManager->clean();
}

// Method to create background asset
void GameOverLevel::createBackground()
{
	factory->createBackground();
	factory->createBackgroundWhiteBorder();
}


// Method to create buttons
void GameOverLevel::createButtons()
{

	//Creates play button entity and position accordingly	
#pragma region PlayButton


	const Vector3  buttonTextColor(0.902, 0.451, 0);

	Entity* retryButtonGameobject = factory->createButtonWithText(BUTTON_UI_PATH + "b_1.png", "Play", buttonTextColor, "PlayButton");
	ButtonRenderer* retryButton = (ButtonRenderer*)retryButtonGameobject->getComponent(eComponentType::RENDER_COMPONENT);
	retryButton->getTextComponent()->setFont(BITMAP_TIMES_ROMAN_24);
	retryButton->getTextComponent()->setOffset(Vector2(-20, -5));




	retryButton->addListenersOnButtonHover([this]()
		{
			playOnce(ON_HOVER_SFX);
		});
	retryButton->addListenersOnButtonHoverExit([this]()
		{
			stopPlaying(ON_HOVER_SFX);
		});
	retryButton->addListenersOnButtonPress([this]()
		{

			playOnce(ON_CLICK_SFX);
			
			restartLevel();
		});

	retryButtonGameobject->transform.position = Vector3(0, 50, 0);
	retryButtonGameobject->transform.scale = Vector2(0.2f, 0.2f);
#pragma endregion

	//Creates ControlsButton  entity and position accordingly	
//#pragma region ControlsButton
//
//	Entity* optionMenuGameobject = factory->createButtonWithText(BUTTON_UI_PATH + "b_1.png", "Controls", buttonTextColor, "Option Button");
//
//	ButtonRenderer* controlButton = (ButtonRenderer*)optionMenuGameobject->getComponent(eComponentType::RENDER_COMPONENT);
//	controlButton->getTextComponent()->setFont(BITMAP_TIMES_ROMAN_24);
//	controlButton->getTextComponent()->setOffset(Vector2(-40, -5));
//
//
//
//	// Events OnButton hover,Click and HoverExit
//	controlButton->addListenersOnButtonHover([this]()
//		{
//			playOnce(ON_HOVER_SFX);
//		});
//
//	controlButton->addListenersOnButtonPress([this]()
//		{
//			playOnce(ON_CLICK_SFX);
//		});
//
//	controlButton->addListenersOnButtonHoverExit([this]()
//		{
//			stopPlaying(ON_HOVER_SFX);
//
//		});
//
//	//Update position and scale
//	optionMenuGameobject->transform.position = Vector3(0, -50, 0);
//	optionMenuGameobject->transform.scale = Vector2(0.2f, 0.2f);
//#pragma endregion
//
//	//Creates Credit button  entity and position accordingly	
//#pragma region CreditButton
//
//	Entity* creditGameObject = factory->createButtonWithText(BUTTON_UI_PATH + "b_1.png", "Credits", buttonTextColor, "Credit Button");
//
//	ButtonRenderer* creditButton = (ButtonRenderer*)creditGameObject->getComponent(eComponentType::RENDER_COMPONENT);
//	creditButton->getTextComponent()->setFont(BITMAP_TIMES_ROMAN_24);
//	creditButton->getTextComponent()->setOffset(Vector2(-30, -5));
//
//
//	// Events OnButton hover,Click and HoverExit
//	creditButton->addListenersOnButtonHover([this]()
//		{
//			playOnce(ON_HOVER_SFX);
//
//
//		});
//
//	creditButton->addListenersOnButtonPress([this]()
//		{
//			playOnce(ON_CLICK_SFX);
//
//		});
//
//	creditButton->addListenersOnButtonHoverExit([this]()
//		{
//			stopPlaying(ON_HOVER_SFX);
//		});
//
//
//	//Update position and scale
//	creditGameObject->transform.position = Vector3(0, -150, 0);
//	creditGameObject->transform.scale = Vector2(0.2f, 0.2f);
//#pragma endregion

}

//Checks and stops the sound if it is playing
void GameOverLevel::stopPlaying(const std::string& fileName)
{
	if (App::IsSoundPlaying(fileName.c_str()))
	{
		App::StopSound(fileName.c_str());
	}
}

//Plays the sound once
void GameOverLevel::playOnce(const std::string& fileName)
{
	App::PlaySound(fileName.c_str(), false);
}

// Plays Background music
void GameOverLevel::playBackgroundMusic(const std::string& fileName)
{
}

bool GameOverLevel::isLevelCompleted()
{
	return false;
}




