#include "stdafx.h"
#include "SceneManager.h"

CSceneManager& CSceneManager::GetInstance()
{
	static CSceneManager instance;
	return instance;
}

void CSceneManager::AddScene(std::string sceneName, CBaseScene* scene)
{  
	m_listOfScenes[sceneName] = scene;
}

void CSceneManager::RemoveScene(std::string sceneName)
{
	m_listOfScenes.erase(sceneName);
}

void CSceneManager::Start()
{
	CEntityManager::GetInstance().Start();

}

void CSceneManager::Update()
{
	CEntityManager::GetInstance().Update();

	if (m_currentScene == nullptr) return;

	m_currentScene->Update();

	
}

void CSceneManager::Render()
{
	CEntityManager::GetInstance().Render();

	if (m_currentScene == nullptr) return;

	m_currentScene->Render();
	
}

void CSceneManager::CleanScene()
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->CleanScene();
	}

	it = m_listOfScenes.begin();

	for (it = m_listOfScenes.begin(); it != m_listOfScenes.end(); ++it)
	{
		it->second = nullptr;
		delete it->second;
	}

	m_listOfScenes.clear();
	
}



void CSceneManager::ChangeScene(std::string changeSceneName)
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->CleanScene();
	}

	m_currentScene = GetScene(changeSceneName);

	m_currentScene->Start();
}

CBaseScene* CSceneManager::GetScene(std::string sceneName)
{
	return m_listOfScenes[sceneName];
}
