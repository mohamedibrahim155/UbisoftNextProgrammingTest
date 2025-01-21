#include "stdafx.h"
#include "LevelManager.h"
#include "../LevelManager/Levels/Level1.h"
#include "../LevelManager/Levels/Level2.h"
#include "../LevelManager/Levels/Level3.h"
#include "../LevelManager/Levels/MainMenu.h"
#include "../LevelManager/Levels/CompletedLevel.h"
#include "../LevelManager/Levels/GameOverLevel.h"
#include "../LevelManager/Levels/ControlsLevel.h"
#include "../ECS/Components/Camera/Camera.h"
#include "../InputManager/InputManager.h"
LevelManager& LevelManager::GetInstance()
{
	static LevelManager instance;
	return instance;
}

void LevelManager::addLevel(eScene sceneName, BaseLevel* scene)
{  
	scene->entityManager = m_entityManager;
	scene->systemManager = m_systemManager;

	m_listOfScenes[sceneName] = scene;
}

void LevelManager::removeLevel(eScene sceneName)
{
	m_listOfScenes.erase(sceneName);
}



void LevelManager::setManagers(SystemManager* systemManager, EntityManager* entityManager)
{
	this->m_entityManager = entityManager;
	this->m_systemManager = systemManager;
}

void LevelManager::createLevels()
{
	//Game UI screens
	BaseLevel* mainMenu = new MainMenu();
	BaseLevel* completedLevel = new CompletedLevel();
	BaseLevel* gameOver = new GameOverLevel();
	BaseLevel* controls = new ControlsLevel();

	// Gameplay Levels
	BaseLevel* level1 = new Level1();
	BaseLevel* level2 = new Level2();
	BaseLevel* level3 = new Level3();


}



void LevelManager::cleanScene()
{
	if (m_currentScene)
	{
		m_currentScene->cleanScene();
	}

	while (m_listOfScenes.size() > 0)
	{
		it = m_listOfScenes.begin();
		delete it->second;
	}

	m_listOfScenes.clear();

	m_entityManager->clean();
	m_systemManager->cleanups();

	
}


void LevelManager::changeScene(eScene changeScene)
{
	if (m_currentScene)
	{
		m_currentScene->cleanScene();
		m_entityManager->clean();
	}


	
	m_currentScene = getScene(changeScene);
	m_currentSceneType = changeScene;
	m_currentSceneName = m_currentScene->getName();

	startLevel();

}

void LevelManager::queSceneChange(eScene changeScene)
{
	m_pendingSceneToLoad = changeScene;
}

void LevelManager::update(float deltaTime)
{
	// checks of there's any scene transition happening
	if (m_pendingSceneToLoad != eScene::NONE)
	{
		// changes the state of current scene
		changeScene(m_pendingSceneToLoad);
		// refres
		m_pendingSceneToLoad = eScene::NONE;
		return;
	}

	if (m_currentScene == nullptr)
	{
		return;
	}

	/*if (m_currentScene->isLevelCompleted())
	{
		m_currentScene->cleanScene();
		m_currentScene = nullptr;
		nextLevel();
		return;
	}*/


	updateSystem(deltaTime);
}

void LevelManager::updateSystem(float deltaTime)
{

	if (InputManager::GetInstance().getKeyDown('V'))
	{
		bool debug = m_systemManager->IsDebug();

		m_systemManager->setDebugVisible(!debug);
	}
	m_systemManager->updateSystems(deltaTime);

}

void LevelManager::render()
{
	if (m_currentScene == nullptr) return;

	m_systemManager->render();
}

void LevelManager::startLevel()
{

	m_systemManager->start();

	InputManager::GetInstance().refreshInputs();

	createCamera();

	m_currentScene->start();


}

eScene LevelManager::nextLevel()
{
	int currentLevel = (int)m_currentSceneType;
	currentLevel++;

	if (currentLevel >= m_listOfScenes.size())
	{
		currentLevel = 0;
	}

	return (eScene)currentLevel;
}

void LevelManager::restartLevel()
{
	queSceneChange(m_currentSceneType);
}

void LevelManager::createCamera()
{
	Entity* camera = m_entityManager->createEntity();
	camera->addComponent(Camera::createCamera());
	camera->setTag("mainCamera");
}

BaseLevel* LevelManager::getScene(eScene scene)
{
	return m_listOfScenes[scene];
}

BaseLevel* LevelManager::getCurrentScene()
{
	return m_listOfScenes[m_currentScene->getType()];
}
