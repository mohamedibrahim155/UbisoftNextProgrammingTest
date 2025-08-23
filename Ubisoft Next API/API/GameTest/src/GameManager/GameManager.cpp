#include "stdafx.h"
#include "GameManager.h"
#include "../src/ECS/Components/UI/ButtonRenderer.h"
#include "../src/LevelManager/LevelManager.h"
#include "../src/LevelManager/Levels/CompletedLevel.h"
#include "../src/LevelManager/Levels/GameOverLevel.h"



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
	CompletedLevel* completedLevel = (CompletedLevel*)LevelManager::GetInstance().getScene(LEVEL_COMPLETE);
	
	// storing next level information to load for the button click next level
	eScene getNextLevelToLoad = LevelManager::GetInstance().nextLevel();
	completedLevel->setNextLevelToLoad(getNextLevelToLoad);

	LevelManager::GetInstance().queSceneChange(LEVEL_COMPLETE);


}

void GameManager::gameOver()
{
	GameOverLevel* gameOverLevel = (GameOverLevel*)LevelManager::GetInstance().getScene(GAME_OVER);

	//gets the current level before transitioning to GameOver Scene
	eScene retryLevel = LevelManager::GetInstance().getCurrentScene()->getType();
	// set the retry level 
		gameOverLevel->setRetryLevel(retryLevel);

		// loads the game Over Scene

		LevelManager::GetInstance().queSceneChange(GAME_OVER);
		reset();

}



void GameManager::reset()
{
	m_currentStroke = 0;
	m_score = 0;

	// clears all the manager's event
	OnScoreChanged.clear();
	onStrikeValueChanged.clear();
	onStrokeCompleted.clear();
}

void GameManager::updateStrike()
{

	if (m_currentStroke >= m_maxStroke)
	{
		onStrokeCompleted.Invoke();
		m_currentStroke = 0;
		return;
	}

	m_currentStroke++;

	onStrikeValueChanged.Invoke();
}

void GameManager::updateScore()
{
	m_score += scoreMultiplier();

	OnScoreChanged.Invoke(m_score);
}

int GameManager::scoreMultiplier()
{
	if (m_currentStroke <= 0) return 0;

	float ratio = static_cast<float>(m_maxStroke) / m_currentStroke;

	int total = static_cast<int>(ratio * m_scoreMultiplier);

	return total;

	return total;
}

