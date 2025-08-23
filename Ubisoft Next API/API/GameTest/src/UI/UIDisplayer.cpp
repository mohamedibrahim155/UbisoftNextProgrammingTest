#include "stdafx.h"
#include "UIDisplayer.h"
#include "../src/ECS/Entity.h"
#include "../src/GameManager/GameManager.h"

UIDisplayer::UIDisplayer(eUIType type) : BaseScriptComponent(), m_type(type)
{
}

void UIDisplayer::start()
{

	m_displayText =  new TextRenderer("");
	m_displayText->setFont(BITMAP_HELVETICA_18);
	m_displayText->setColor(0,0,0);
	gameObject->addComponent(m_displayText);

	updateUI();
}

void UIDisplayer::updateComponent()
{
	if (!m_displayText) return;



}

void UIDisplayer::updateUI()
{

	switch (m_type)
	{
	case eUIType::NONE:
		break;
	case eUIType::SCORE:

		//int currentScore = GameManager::GetInstance().getScore();

		prefixText = "Score : ";

		setUIText(std::to_string(GameManager::GetInstance().getScore()));

		GameManager::GetInstance().OnScoreChanged.Subscribe([this](int score)
			{
				setUIText(std::to_string(score));

			});

		break;
	case eUIType::STROKE:

		int currentStroke = GameManager::GetInstance().getCurrentStrike();
		int maxStrike = GameManager::GetInstance().getMaxtrike();

		prefixText = "Stroke : ";

		setUIText(std::to_string(currentStroke) + " / " + std::to_string(maxStrike));


		GameManager::GetInstance().onStrikeValueChanged.Subscribe([this]()
			{
				int updatedStroke = GameManager::GetInstance().getCurrentStrike();
				int updateMaxStroke = GameManager::GetInstance().getMaxtrike();

				setUIText(std::to_string(updatedStroke) + " / " + std::to_string(updateMaxStroke));

			});

		break;
	}
}

void UIDisplayer::setUIText(const std::string& value)
{
	if (!m_displayText) return;

	m_displayText->setText(prefixText + value);
}

