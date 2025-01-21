#pragma once
#include <unordered_map>
#include "../src/Events/Event.h"
class GameManager
{
public:

	static GameManager& GetInstance();

	void setMaxStroke(int strokeChances);
	void showLevelComplete();
	void gameOver();
	void strike();
	void reset();

	void updateStrike();
	void updateScore(int value);
	

	int getCurrentStrike() { return m_currentStroke; }
	int getMaxtrike() { return m_maxStroke; }
	int getScore() { return m_score; }

	CEvent<> onStrokeCompleted;
	CEvent<int> OnScoreChanged;
	CEvent<> onStrikeValueChanged;

private:

	//EntityManager* m_entityManager;

	int m_maxStroke = 5;
	int m_currentStroke = 0;
	int m_score = 0;


};

