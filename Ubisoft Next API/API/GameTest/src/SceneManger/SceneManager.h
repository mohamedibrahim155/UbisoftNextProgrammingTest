#pragma once
#include "BaseScene.h"
#include <unordered_map>
#include "../src/ECS/EntityManager.h"
#include "../src/ECS/SystemManager.h"
class   LevelManager
{
public:
	static LevelManager& GetInstance();

	void AddLevel(eScene sceneEnum, CBaseScene* scene);
	void RemoveLevel(eScene sceneEnum);
	void SetManagers(SystemManager* m_systemManager, EntityManager* m_entityManager);
	void Init();
	void CleanScene();
	void ChangeScene(eScene changeScene);

	CBaseScene* GetScene(eScene scene);

private:

	std::unordered_map<eScene, CBaseScene*>::iterator it;
	std::unordered_map<eScene, CBaseScene*> m_listOfScenes;

	eScene m_currentSceneType = eScene::SCENE_1;
	std::string m_currentSceneName = "Untitled";

	CBaseScene* m_currentScene;

	SystemManager* m_systemManager;
	EntityManager* m_entityManager;


};

