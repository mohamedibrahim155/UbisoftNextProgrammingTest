#include "stdafx.h"
#include "CompletedLevel.h"
#include "../src//GameManager/GameManager.h"
CompletedLevel::CompletedLevel() : BaseLevel(LEVEL_COMPLETE)
{
    m_factory = new GameObjectFactory(entityManager);
}

CompletedLevel::~CompletedLevel()
{
	if (m_factory)
	{
		delete m_factory;
	}
}

void CompletedLevel::start()
{
	createBackgound();
	createPopUp();
}

void CompletedLevel::cleanScene()
{
	systemManager->cleanSystem();
}

bool CompletedLevel::isLevelCompleted()
{
    return false;
}

void CompletedLevel::setScoreText(int score)
{
	if (!text) return;
	std::string scoreText = "Scrore : " +  std::to_string(score);
	text->setText(scoreText);
}

void CompletedLevel::createPopUp()
{
	Entity* gameObject1 = entityManager->createEntity();

	ButtonRenderer* button = new ButtonRenderer(LEVEL_COMPLETE_BUTTON);

	button->addListenersOnButtonPress([this]()
		{
			//GameManager::GetInstance().OnLevelCompleteClick(true);
		});

	gameObject1->addComponent(button);

	gameObject1->transform.position = Vector2(150, -100);

	


	Entity* gameObject2 = entityManager->createEntity();

	ButtonRenderer* mainMenu = new ButtonRenderer(MAINMENU_BUTTON);

	mainMenu->addListenersOnButtonPress([this]()
		{
			loadScene(MAINMENU);
		});

	gameObject2->addComponent(mainMenu);


	gameObject2->transform.position =  Vector2(-200, -100);


	Entity* textGameObject = entityManager->createEntity();
	
	text = new TextRenderer("");
	text->setColor(0.8, 0.2, 0.3);

	textGameObject->addComponent(text);
	textGameObject->transform.position = Vector2(-70, 0);


	Entity* completedTextGameObject = entityManager->createEntity();

	TextRenderer* completedText= new TextRenderer("LEVEL COMPLETED !");
	completedText->setColor(0.5, 0.2, 0);
	completedText->setFont(BITMAP_TIMES_ROMAN_24);

	completedTextGameObject->addComponent(completedText);
	completedTextGameObject->transform.position = Vector2(-150, 50);

	setScoreText(GameManager::GetInstance().getScore());
	
}

void CompletedLevel::createBackgound()
{
	m_factory->createBackground(BACKGROUND_TEXTURE_PATH);

}
