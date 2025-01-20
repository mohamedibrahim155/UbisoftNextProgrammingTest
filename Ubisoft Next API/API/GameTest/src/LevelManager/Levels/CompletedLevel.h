#pragma once
#include "../BaseLevel.h"
#include "../src/ECS/Components/UI/ButtonRenderer.h"
#include "../src/Factory/GameObjectFactory.h"
class CompletedLevel : public BaseLevel
{
public:

	CompletedLevel();

		~CompletedLevel() override;
	// Inherited via BaseLevel
	void start() override;

	void cleanScene() override;

	bool isLevelCompleted() override;

private:


	const std::string LEVEL_COMPLETE_BUTTON = ASSET_PATH + "\\UI\\Button\\levelComplete.png";
	const std::string MAINMENU_BUTTON = ASSET_PATH + "\\UI\\Button\\mainmenu.png";
	GameObjectFactory* m_factory;

	TextRenderer* m_scoreText = nullptr;

	void createPopUp();
	void createBackgound();
	void setScoreText(int score);

};

