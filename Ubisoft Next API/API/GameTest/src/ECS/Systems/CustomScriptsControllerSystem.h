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
	void update(std::vector<Entity*> entities, float deltaTime) override;
	void render(std::vector<Entity*> entities) override;
	void cleanups() override;

	std::vector<BaseScriptComponent*> getScripts() const;

private:

	bool ContainsScript(EntityID id);
	
	void addScript(Entity* entity);
	void removeScript(Entity* entity);
	
	void HandleOnEntityAdded(Entity* entity);
	void HandleOnComponentAdded(IComponent* component, Entity* entity);

	std::vector<std::pair<Entity*,BaseScriptComponent*>> m_listofScripts;

};

