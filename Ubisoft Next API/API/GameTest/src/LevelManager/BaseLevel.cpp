#include "stdafx.h"
#include "BaseLevel.h"

#include "LevelManager.h"
BaseLevel::BaseLevel(eScene sceneType) : m_sceneType(sceneType)
{
	LevelManager::GetInstance().AddLevel(m_sceneType, this);
}

BaseLevel::~BaseLevel()
{
	LevelManager::GetInstance().RemoveLevel(m_sceneType);
}



void BaseLevel::ChangeScene(eScene changeScene)
{
	LevelManager::GetInstance().ChangeScene(changeScene);
}

eScene BaseLevel::GetType()
{
	return (m_sceneType);
}
