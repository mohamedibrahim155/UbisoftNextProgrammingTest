#include "stdafx.h"
#include "BaseLevel.h"

#include "LevelManager.h"
BaseLevel::BaseLevel(eScene sceneType) : m_sceneType(sceneType)
{
	LevelManager::GetInstance().addLevel(m_sceneType, this);
}

BaseLevel::~BaseLevel()
{
	LevelManager::GetInstance().removeLevel(m_sceneType);
}



void BaseLevel::changeScene(eScene changeScene)
{
	LevelManager::GetInstance().changeScene(changeScene);
}

void BaseLevel::RestartLevel()
{
	LevelManager::GetInstance().RestartLevel();
}



eScene BaseLevel::getType()
{
	return (m_sceneType);
}
