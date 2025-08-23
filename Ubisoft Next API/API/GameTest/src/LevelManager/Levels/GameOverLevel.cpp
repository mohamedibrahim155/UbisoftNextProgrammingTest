
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
	factory->createSpriteObject(GAMEOVER_UI, Vector2::Zero(), 0);
}


// Method to create buttons
void GameOverLevel::createButtons()
{

	//Creates play button entity and position accordingly	
#pragma region PlayButton


	const Vector3  buttonTextColor(0.902, 0.451, 0);

	Entity* retryButtonGameobject = factory->createButton(RETRY_UI);
	ButtonRenderer* retryButton = (ButtonRenderer*)retryButtonGameobject->getComponent(eComponentType::RENDER_COMPONENT);




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
		
			loadScene(m_retryLevel);
		});

	retryButtonGameobject->transform.position = Vector3(0, -150, 0);
	retryButtonGameobject->transform.scale = Vector2(1, 1);



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

void GameOverLevel::setRetryLevel(eScene retyLevel)
{
	m_retryLevel = retyLevel;
}




