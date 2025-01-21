///////////////////////////////////////////////////////////////////////////////
// Filename: LevelManager.h
//  Updates and from the world
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "BaseLevel.h"
#include <unordered_map>
#include "../src/ECS/EntityManager.h"
#include "../src/ECS/SystemManager.h"

///--------------------------------------------------------------------------
//  Singleton class responsible for handling scene change
// handle the update of system manager
//--------------------------------------------------------------------------
class   LevelManager
{
public:
	static LevelManager& GetInstance();

	//add level to map
	void addLevel(eScene sceneEnum, BaseLevel* scene);
	void removeLevel(eScene sceneEnum);

	//initial references of managers to create entities
	void setManagers(SystemManager* m_systemManager, EntityManager* m_entityManager);

	//creates different levels
	void createLevels();

	//clean entities from system
	void cleanScene();

	// scene transition sets in a que
	void queSceneChange(eScene changeScene);

	//updates system manager based on current active level
	void update(float deltaTime);

	//renders system manager based on current active level
	void render();

	//returns next active level
	eScene nextLevel();

	// refresh current scene
	void restartLevel();

	//getters
	BaseLevel* getScene(eScene scene);
	BaseLevel* getCurrentScene();
private:

private:

	//Holds the different levels
	std::unordered_map<eScene, BaseLevel*> m_listOfScenes;
	std::unordered_map<eScene, BaseLevel*>::iterator it;

	eScene m_currentSceneType = eScene::LEVEL_1;
	eScene m_pendingSceneToLoad = eScene::NONE;
	std::string m_currentSceneName = "Untitled";

	BaseLevel* m_currentScene;

	//gives references to each level to create entities
	SystemManager* m_systemManager;
	EntityManager* m_entityManager;

	//Inits scene
	void startLevel();

	//updates system manager
	void updateSystem(float deltaTime);

	// creates camera while init
	void createCamera();

	//changes state of current scene to different scene
	void changeScene(eScene changeScene);
};

