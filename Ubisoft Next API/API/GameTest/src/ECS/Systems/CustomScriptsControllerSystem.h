#pragma once
#include "../System.h"
#include <vector>
#include "../src/ECS/Components/Scripts/ScriptComponent.h"

class CustomScriptsControllerSystem : public ISystem
{
public:
	CustomScriptsControllerSystem() : ISystem("CustomScriptControllerSystem", eSystemType::CUSTOMSCRIPT_SYSTEM) {};
	// Inherited via ISystem
	void start(std::vector<Entity*> entities) override;
	void Update(std::vector<Entity*> entities, float deltaTime) override;
	void render(std::vector<Entity*> entities) override;
	void Cleanups() override;

	std::vector<ScriptComponentBase*> GetScripts() const;

private:

};

