#pragma once
#include "BaseLevel.h"
#include <unordered_map>
#include "../src/ECS/EntityManager.h"
#include "../src/ECS/SystemManager.h"
class   LevelManager
{
public:
	static LevelManager& GetInstance();

	void addLevel(eScene sceneEnum, BaseLevel* scene);
	void removeLevel(eScene sceneEnum);
	void setManagers(SystemManager* m_systemManager, EntityManager* m_entityManager);
	void createLevels();
	void cleanScene();
	void queSceneChange(eScene changeScene);
	void update(float deltaTime);
	void render();
	void nextLevel();
	void restartLevel();
	void loseLevel();

	BaseLevel* getScene(eScene scene);
	BaseLevel* getCurrentScene();
private:

private:

	std::unordered_map<eScene, BaseLevel*>::iterator it;
	std::unordered_map<eScene, BaseLevel*> m_listOfScenes;

	eScene m_currentSceneType = eScene::LEVEL_1;
	eScene m_pendingSceneToLoad = eScene::NONE;
	std::string m_currentSceneName = "Untitled";

	BaseLevel* m_currentScene;


	SystemManager* m_systemManager;
	EntityManager* m_entityManager;

	void startLevel();
	void updateSystem(float deltaTime);
	void createCamera();
	void changeScene(eScene changeScene);
};

