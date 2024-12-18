#pragma once
#include "../System.h"
#include <vector>
#include "../src/ECS/Components/ScriptComponent.h"

class CustomScriptsControllerSystem : public ISystem
{
public:
	CustomScriptsControllerSystem() : ISystem("CustomScriptControllerSystem") {};
	// Inherited via ISystem
	void Start() override;
	void Update(std::vector<Entity*> entities, float deltaTime) override;
	void Render(std::vector<Entity*> entities) override;
	void Cleanups() override;

	std::vector<ScriptComponent*> GetScripts() const;

private:
	std::vector<ScriptComponent*> listOfScripts;

};

