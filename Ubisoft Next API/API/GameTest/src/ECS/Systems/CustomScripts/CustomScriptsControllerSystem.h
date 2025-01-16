#pragma once
#include "../../System.h"
#include <vector>
#include "../src/ECS/Components/Scripts/ScriptComponent.h"

class CustomScriptsControllerSystem : public ISystem
{
public:
	CustomScriptsControllerSystem() : ISystem("CustomScriptControllerSystem", eSystemType::CUSTOMSCRIPT_SYSTEM) {};
	
	// Inherited via ISystem
	void start(std::vector<Entity*> entities) override;
	void subscribeEvents();
	void update(std::vector<Entity*> entities, float deltaTime) override;
	void render(std::vector<Entity*> entities, bool isDebugVisible) override;
	void cleanups() override;

	std::vector<BaseScriptComponent*> getScripts() const;

private:

	bool containsScriptComponent(EntityID id);
	
	void addScript(Entity* entity);
	void removeScript(Entity* entity);
	
	void handleOnEntityAdded(Entity* entity);
	void handleOnComponentAdded(IComponent* component, Entity* entity);

	std::vector<std::pair<Entity*,BaseScriptComponent*>> m_listofScripts;

	bool m_isRefreshed = false;

};

