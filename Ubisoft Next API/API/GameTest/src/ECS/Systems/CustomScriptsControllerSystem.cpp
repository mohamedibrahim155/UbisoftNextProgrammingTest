#include "stdafx.h"
#include "CustomScriptsControllerSystem.h"
#include "../SystemManager.h"
void CustomScriptsControllerSystem::start(std::vector<Entity*> entities)
{
	for (Entity* entity : entities)
	{
		addScript(entity);
	}


	systemManager->OnEntityAdded.Subscribe([this](Entity* entity)
		{
			entity->OnComponentAdded.Subscribe([this, entity](IComponent* component)
				{
					addScript(entity);
				});
			
		});


	systemManager->OnEntityRemoved.Subscribe([this](Entity* entity)
		{
			removeScript(entity);
		});
}

void CustomScriptsControllerSystem::update(std::vector<Entity*> entities, float deltaTime)
{


	for (const std::pair<Entity*,ScriptComponentBase*>&  scriptEntity:  listofScripts)
	{
		Entity* entity = scriptEntity.first;
		ScriptComponentBase* scriptComponent = scriptEntity.second;

		if (!entity->IsActive() || entity->isDestroyed) continue;

		if (!scriptComponent->isComponentEnabled) continue;

		if (!scriptComponent->isStartInvoked)
		{
			scriptComponent->start();
			scriptComponent->isStartInvoked = true;
			continue;
		}

		
		scriptComponent->updateComponent();

	}
}

void CustomScriptsControllerSystem::render(std::vector<Entity*> entities)
{
	for (const std::pair<Entity*, ScriptComponentBase*>& scriptEntity : listofScripts)
	{
		Entity* entity = scriptEntity.first;
		ScriptComponentBase* scriptComponent = scriptEntity.second;

		if (!entity->IsActive() || entity->isDestroyed) continue;

		if (!scriptComponent->isComponentEnabled) continue;

		scriptComponent->render();

	}
}

void CustomScriptsControllerSystem::cleanups()
{
	listofScripts.clear();
}

std::vector<ScriptComponentBase*> CustomScriptsControllerSystem::getScripts() const
{
	return std::vector<ScriptComponentBase*>();
}

void CustomScriptsControllerSystem::addScript(Entity* entity)
{
	ScriptComponentBase* script = (ScriptComponentBase*)entity->GetComponent(ComponentType::SCRIPT_COMPONENT);

	if (!script) return;

	listofScripts.emplace_back(entity,script);
}

void CustomScriptsControllerSystem::removeScript(Entity* entity)
{

	for (auto it = listofScripts.begin(); it != listofScripts.end(); ++it)
	{
		if ( it->first->getID() == entity->getID())
		{
			listofScripts.erase(it);
			return;
		}
	}
}
