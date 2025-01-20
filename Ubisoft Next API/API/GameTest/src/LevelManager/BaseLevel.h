#pragma once

#include <string>
#include <map>
#include "../src/ECS/EntityManager.h"
#include "../src/ECS/SystemManager.h"
class LevelManager;
enum eScene
{
	NONE = -1,
	MAINMENU = 0,
	LEVEL_COMPLETE = 1,
	GAME_OVER = 2,
	LEVEL_1 = 3,
	LEVEL_2 = 4,
	LEVEL_3 = 5,


};

class BaseLevel
{
public:

	BaseLevel(eScene sceneType);
	virtual ~BaseLevel();

	virtual void start() = 0;
	virtual void cleanScene() = 0;
	virtual bool isLevelCompleted() = 0;
	virtual eScene getType();

	void loadScene(eScene eScene);
	void restartLevel();

	inline std::string getName() { return sceneToString[m_sceneType]; };

	SystemManager* systemManager;
	EntityManager* entityManager;

protected:

	eScene m_sceneType;

	std::map<eScene, std::string> sceneToString = { {LEVEL_1, "Scene1"},
													{LEVEL_2, "Scene2"}, 
												   { MAINMENU, "MainMenu" } };

	
};

