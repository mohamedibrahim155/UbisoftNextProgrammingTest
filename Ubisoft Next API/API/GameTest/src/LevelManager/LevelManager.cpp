#include "stdafx.h"
#include "LevelManager.h"
#include "../LevelManager/Levels/Level1.h"
#include "../LevelManager/Levels/Level2.h"
LevelManager& LevelManager::GetInstance()
{
	static LevelManager instance;
	return instance;
}

void LevelManager::AddLevel(eScene sceneName, BaseLevel* scene)
{  
	scene->entityManager = m_entityManager;
	scene->systemManager = m_systemManager;

	m_listOfScenes[sceneName] = scene;
}

void LevelManager::RemoveLevel(eScene sceneName)
{
	m_listOfScenes.erase(sceneName);
}



void LevelManager::SetManagers(SystemManager* systemManager, EntityManager* entityManager)
{
	this->m_entityManager = entityManager;
	this->m_systemManager = systemManager;
}

void LevelManager::Init()
{
	BaseLevel* level1 = new Level1();
	BaseLevel* level2 = new Level2();
}



void LevelManager::CleanScene()
{
	if (m_currentScene)
	{
		m_currentScene->CleanScene();
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


void LevelManager::ChangeScene(eScene changeScene)
{
	if (m_currentScene)
	{
		m_currentScene->CleanScene();
	}

	m_currentScene = GetScene(changeScene);
	m_currentSceneType = m_currentScene->GetType();
	m_currentSceneName = m_currentScene->GetName();

	m_currentScene->Initialize();
}

BaseLevel* LevelManager::GetScene(eScene scene)
{
	return m_listOfScenes[scene];
}
