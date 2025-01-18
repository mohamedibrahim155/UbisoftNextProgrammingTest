#pragma once

#include <string>
#include <map>
#include "../src/ECS/EntityManager.h"
#include "../src/ECS/SystemManager.h"
class LevelManager;
enum eScene
{
	MAINMENU = 0,
	LEVEL_1 = 1,
	LEVEL_2 = 2,
};

class BaseLevel
{
public:

	BaseLevel(eScene sceneType);
	virtual ~BaseLevel();

	virtual void initialize() = 0;
	virtual void cleanScene() = 0;
	virtual bool isLevelCompleted() = 0;
	virtual eScene getType();

	void changeScene(eScene eScene);
	void RestartLevel();

	inline std::string getName() { return sceneToString[m_sceneType]; };

	SystemManager* systemManager;
	EntityManager* entityManager;

protected:

	eScene m_sceneType;

	std::map<eScene, std::string> sceneToString = { {LEVEL_1, "Scene1"},
													{LEVEL_2, "Scene2"}, 
												   { MAINMENU, "MainMenu" } };

	
};

