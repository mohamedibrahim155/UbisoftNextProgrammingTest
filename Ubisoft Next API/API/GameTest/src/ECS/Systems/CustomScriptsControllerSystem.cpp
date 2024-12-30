#include "stdafx.h"
#include "CustomScriptsControllerSystem.h"

void CustomScriptsControllerSystem::start(std::vector<Entity*> entities)
{
}

void CustomScriptsControllerSystem::Update(std::vector<Entity*> entities, float deltaTime)
{
	for (Entity* entity :  entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;
		ScriptComponentBase* scriptComponent = (ScriptComponentBase*)entity->GetComponent(ComponentType::SCRIPT_COMPONENT);

		if (scriptComponent == nullptr) continue;

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
}

void CustomScriptsControllerSystem::Cleanups()
{
}

std::vector<ScriptComponentBase*> CustomScriptsControllerSystem::GetScripts() const
{
	return std::vector<ScriptComponentBase*>();
}
