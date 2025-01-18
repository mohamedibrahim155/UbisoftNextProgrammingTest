#include "stdafx.h"
#include "LevelManager.h"
#include "../LevelManager/Levels/Level1.h"
#include "../LevelManager/Levels/Level2.h"
#include "../LevelManager/Levels/MainMenu.h"
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

void LevelManager::Init()
{
	BaseLevel* mainMenu = new MainMenu();
	BaseLevel* level1 = new Level1();
	BaseLevel* level2 = new Level2();
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

	delete m_systemManager;
	delete m_entityManager;
}


void LevelManager::changeScene(eScene changeScene)
{
	
	if (m_currentScene)
	{
		m_entityManager->clean();
		m_currentScene->cleanScene();
	}

	
	m_currentScene = getScene(changeScene);
	m_currentSceneType = m_currentScene->getType();
	m_currentSceneName = m_currentScene->getName();

	initCurrentScene();
}

void LevelManager::update(float deltaTime)
{
	if (m_currentScene == nullptr)
	{
		return;
	}

	if (m_currentScene->isLevelCompleted())
	{
		Timer::GetInstance().unscaledTime = 0;
		m_currentScene->cleanScene();
		m_currentScene = nullptr;
		InputManager::GetInstance().refreshInputs();
		nextLevel();
		return;
	}


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

void LevelManager::initCurrentScene()
{
	m_systemManager->start();

	createCamera();

	m_currentScene->initialize();
}

void LevelManager::nextLevel()
{
	int currentLevel = (int)m_currentSceneType;
	currentLevel++;

	if (currentLevel >= m_listOfScenes.size())
	{
		currentLevel = 0;
	}

	changeScene((eScene)currentLevel);
}

void LevelManager::restartLevel()
{
	m_currentScene->cleanScene();
	
	initCurrentScene();
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
