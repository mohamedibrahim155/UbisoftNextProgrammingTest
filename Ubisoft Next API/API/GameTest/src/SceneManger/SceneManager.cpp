#include "stdafx.h"
#include "SceneManager.h"

CSceneManager& CSceneManager::GetInstance()
{
	static CSceneManager instance;
	return instance;
}

void CSceneManager::AddScene(eScene sceneName, CBaseScene* scene)
{  
	m_listOfScenes[sceneName] = scene;
}

void CSceneManager::RemoveScene(eScene sceneName)
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


void CSceneManager::ChangeScene(eScene changeScene)
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->CleanScene();
	}

	m_currentScene = GetScene(changeScene);
	m_currentSceneType = m_currentScene->GetType();
	m_currentSceneName = m_currentScene->GetName();

	m_currentScene->Start();
}

CBaseScene* CSceneManager::GetScene(eScene scene)
{
	return m_listOfScenes[scene];
}
