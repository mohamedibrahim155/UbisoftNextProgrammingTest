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



void BaseLevel::loadScene(eScene changeScene)
{
	LevelManager::GetInstance().queSceneChange(changeScene);
}

void BaseLevel::restartLevel()
{
	LevelManager::GetInstance().restartLevel();
}


eScene BaseLevel::getType()
{
	return (m_sceneType);
}
