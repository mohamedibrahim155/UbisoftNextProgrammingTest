#include "stdafx.h"
#include "SceneManager.h"
#include "../SceneManger/Scenes/Level1.h"
#include "../SceneManger/Scenes/Level2.h"
LevelManager& LevelManager::GetInstance()
{
	static LevelManager instance;
	return instance;
}

void LevelManager::AddLevel(eScene sceneName, CBaseScene* scene)
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
	CBaseScene* level1 = new Level1();
	CBaseScene* level2 = new Level2();
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

CBaseScene* LevelManager::GetScene(eScene scene)
{
	return m_listOfScenes[scene];
}
