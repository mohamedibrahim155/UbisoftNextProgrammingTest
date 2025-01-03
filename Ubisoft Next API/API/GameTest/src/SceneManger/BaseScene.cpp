#include "stdafx.h"
#include "BaseScene.h"

#include "SceneManager.h"
CBaseScene::CBaseScene(eScene sceneType) : m_sceneType(sceneType)
{
	LevelManager::GetInstance().AddLevel(m_sceneType, this);
}

CBaseScene::~CBaseScene()
{
	LevelManager::GetInstance().RemoveLevel(m_sceneType);
}



void CBaseScene::ChangeScene(eScene changeScene)
{
	LevelManager::GetInstance().ChangeScene(changeScene);
}

eScene CBaseScene::GetType()
{
	return (m_sceneType);
}
