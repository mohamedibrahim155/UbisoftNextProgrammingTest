#include "stdafx.h"
#include "BaseScene.h"

#include "SceneManager.h"
CBaseScene::CBaseScene(eScene sceneType) : m_sceneType(sceneType)
{
	CSceneManager::GetInstance().AddScene(m_sceneType, this);
}

CBaseScene::~CBaseScene()
{
	CSceneManager::GetInstance().RemoveScene(m_sceneType);
}



void CBaseScene::ChangeScene(eScene changeScene)
{
	CSceneManager::GetInstance().ChangeScene(changeScene);
}

eScene CBaseScene::GetType()
{
	return (m_sceneType);
}
