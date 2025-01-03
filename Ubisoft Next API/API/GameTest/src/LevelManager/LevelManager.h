#pragma once
#include "BaseLevel.h"
#include <unordered_map>
#include "../src/ECS/EntityManager.h"
#include "../src/ECS/SystemManager.h"
class   LevelManager
{
public:
	static LevelManager& GetInstance();

	void AddLevel(eScene sceneEnum, BaseLevel* scene);
	void RemoveLevel(eScene sceneEnum);
	void SetManagers(SystemManager* m_systemManager, EntityManager* m_entityManager);
	void Init();
	void CleanScene();
	void ChangeScene(eScene changeScene);

	BaseLevel* GetScene(eScene scene);

private:

	std::unordered_map<eScene, BaseLevel*>::iterator it;
	std::unordered_map<eScene, BaseLevel*> m_listOfScenes;

	eScene m_currentSceneType = eScene::SCENE_1;
	std::string m_currentSceneName = "Untitled";

	BaseLevel* m_currentScene;

	SystemManager* m_systemManager;
	EntityManager* m_entityManager;


};

