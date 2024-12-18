#include "stdafx.h"
#include "CustomScriptsControllerSystem.h"

void CustomScriptsControllerSystem::Start()
{
}

void CustomScriptsControllerSystem::Update(std::vector<Entity*> entities, float deltaTime)
{
	for (Entity* entity :  entities)
	{
		ScriptComponent* scriptComponent = (ScriptComponent*)entity->GetComponent(ComponentType::SCRIPT_COMPONENT);

		if (scriptComponent == nullptr) continue;

		if (!scriptComponent->isStartInvoked)
		{
			scriptComponent->Start();
			scriptComponent->isStartInvoked = true;
			continue;
		}


		scriptComponent->UpdateComponent();
	}
}

void CustomScriptsControllerSystem::Render(std::vector<Entity*> entities)
{
}

void CustomScriptsControllerSystem::Cleanups()
{
}
