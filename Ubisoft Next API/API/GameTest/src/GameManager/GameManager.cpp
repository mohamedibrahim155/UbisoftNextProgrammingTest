#include "stdafx.h"
#include "GameManager.h"
#include "../src/ECS/Components/UI/ButtonRenderer.h"
#include "../src/LevelManager/LevelManager.h"
#include "../src/LevelManager/Levels/CompletedLevel.h"



GameManager& GameManager::GetInstance()
{
	static GameManager instance;
	return instance;
}

void GameManager::setMaxStroke(int strokeChances)
{
	m_maxStroke = strokeChances;
}

void GameManager::showLevelComplete()
{
	CompletedLevel* level = (CompletedLevel*)LevelManager::GetInstance().getScene(LEVEL_COMPLETE);
	LevelManager::GetInstance().queSceneChange(LEVEL_COMPLETE);


}

void GameManager::gameOver()
{
}

void GameManager::strike()
{

	if (m_currentStroke >= m_maxStroke)
	{
		onStrokeCompleted.Invoke();
		return;
	}

	m_currentStroke++;

}

void GameManager::reset()
{
	m_currentStroke = 0;
}

void GameManager::updateStrike()
{
	if (m_currentStroke >= m_maxStroke)
	{
		onStrokeCompleted.Invoke();
		return;
	}
	m_currentStroke++;
}

void GameManager::updateScore(int value)
{
	m_score = value;
}

