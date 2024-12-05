#pragma once
#include "BaseScene.h"
#include <unordered_map>

class   CSceneManager
{
public:
	static CSceneManager& GetInstance();

	void AddScene(std::string sceneName, CBaseScene* scene);
	void RemoveScene(std::string sceneName);


	void StartScene();
	void UpdateScene();
	void RenderScene();
	void CleanScene();
	void ChangeScene(std::string changeSceneName);

	CBaseScene* GetScene(std::string sceneName);

private:

	std::unordered_map<std::string, CBaseScene*>::iterator it;
	std::unordered_map<std::string, CBaseScene*> m_listOfScenes;

	std::vector<std::string> m_removedScenes;

	eScene m_sceneEnum = eScene::NONE;
	CBaseScene* m_currentScene;


};

