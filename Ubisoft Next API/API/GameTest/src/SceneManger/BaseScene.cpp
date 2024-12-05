#include "stdafx.h"
#include "BaseScene.h"

#include "SceneManager.h"
CBaseScene::CBaseScene(std::string name) : m_sceneName(name)
{
	CSceneManager::GetInstance().AddScene(m_sceneName, this);
}

CBaseScene::~CBaseScene()
{
	CSceneManager::GetInstance().RemoveScene(m_sceneName);
}

void CBaseScene::ChangeScene(std::string changeSceneName)
{
	CSceneManager::GetInstance().ChangeScene(changeSceneName);
}


std::string CBaseScene::GetSceneName()
{
	return m_sceneName;
}
