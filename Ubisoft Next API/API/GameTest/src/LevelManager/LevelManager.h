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
	void Init();
	void cleanScene();
	void changeScene(eScene changeScene);
	void NextLevel();
	void RestartLevel();

	BaseLevel* getScene(eScene scene);

private:

	std::unordered_map<eScene, BaseLevel*>::iterator it;
	std::unordered_map<eScene, BaseLevel*> m_listOfScenes;

	eScene m_currentSceneType = eScene::LEVEL_1;
	std::string m_currentSceneName = "Untitled";

	BaseLevel* m_currentScene;

	SystemManager* m_systemManager;
	EntityManager* m_entityManager;


};

