
///////////////////////////////////////////////////////////////////////////////
// Filename: GameManager.h
//  Singleton class to manager the gameplay states and score
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <unordered_map>
#include "../src/Events/Event.h"
class GameManager
{
public:

	static GameManager& GetInstance();

	void setMaxStroke(int strokeChances);

	// Loads level complete screen
	void showLevelComplete();

	// Loads gameOver scene
	void gameOver();

	//resets properties
	void reset();

	//updates if ball lauched
	void updateStrike();

	// updates score of the game
	void updateScore();
	
	// getters
	int getCurrentStrike() { return m_currentStroke; }
	int getMaxtrike() { return m_maxStroke; }
	int getScore() { return m_score; }

	//events to handle game states
	CEvent<> onStrokeCompleted;
	CEvent<int> OnScoreChanged;
	CEvent<> onStrikeValueChanged;

private:

	//properties
	int m_maxStroke = 5;
	int m_currentStroke = 0;
	int m_score = 0;

	const int m_scoreMultiplier = 100;

	// handles score based on number of strike remaining
	int scoreMultiplier();

};

