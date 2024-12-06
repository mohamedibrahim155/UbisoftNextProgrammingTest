#pragma once
#include "BaseScene.h"
#include <unordered_map>

class   CSceneManager
{
public:
	static CSceneManager& GetInstance();

	void AddScene(eScene sceneEnum, CBaseScene* scene);
	void RemoveScene(eScene sceneEnum);


	void Start();
	void Update();
	void Render();
	void CleanScene();
	void ChangeScene(eScene changeScene);

	CBaseScene* GetScene(eScene scene);

private:

	std::unordered_map<eScene, CBaseScene*>::iterator it;
	std::unordered_map<eScene, CBaseScene*> m_listOfScenes;

	eScene m_currentSceneType = eScene::SCENE_1;
	std::string m_currentSceneName = "Untitled";

	CBaseScene* m_currentScene;


};

