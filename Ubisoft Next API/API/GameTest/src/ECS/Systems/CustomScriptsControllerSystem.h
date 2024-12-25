#pragma once
#include "../System.h"
#include <vector>
#include "../src/ECS/Components/ScriptComponent.h"

class CustomScriptsControllerSystem : public ISystem
{
public:
	CustomScriptsControllerSystem() : ISystem("CustomScriptControllerSystem", eSystemType::CUSTOMSCRIPT_SYSTEM) {};
	// Inherited via ISystem
	void Start(std::vector<Entity*> entities) override;
	void Update(std::vector<Entity*> entities, float deltaTime) override;
	void Render(std::vector<Entity*> entities) override;
	void Cleanups() override;

	std::vector<ScriptComponent*> GetScripts() const;

private:

};

