#pragma once

#include <string>
#include <map>

class CSceneManager;
enum eScene
{
	SCENE_1 = 0,
	SCENE_2 = 1,
	SCENE_3 = 3
};

class CBaseScene
{
public:

	CBaseScene(eScene sceneType);
	virtual ~CBaseScene();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void CleanScene() = 0;
	virtual eScene GetType();

	void ChangeScene(eScene eScene);

	inline std::string GetName() { return sceneToString[m_sceneType]; };

protected:

	eScene m_sceneType;

	std::map<eScene, std::string> sceneToString = { {SCENE_1, "Scene1"},
													{SCENE_2, "Scene2"}, 
												   { SCENE_3, "Scene3" } };


};

