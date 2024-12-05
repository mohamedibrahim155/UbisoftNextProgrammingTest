#pragma once

#include <string>


class CSceneManager;
enum eScene
{
	NONE = 0,
	MAIN_MENU =1,
	LEVEL1 = 2,
	LEVEL2 = 3
};

class CBaseScene
{
public:

	CBaseScene(std::string name);
	virtual ~CBaseScene();

	virtual void StartScene() = 0;
	virtual void UpdateScene() = 0;
	virtual void RenderScene() = 0;
	virtual void CleanScene() = 0;

	void ChangeScene(std::string changeSceneName);
	virtual std::string GetSceneName();

protected:

	std::string m_sceneName;
};

