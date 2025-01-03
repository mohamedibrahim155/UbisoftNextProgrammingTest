#include "stdafx.h"
#include "CustomScriptsControllerSystem.h"
#include "../SystemManager.h"
void CustomScriptsControllerSystem::start(std::vector<Entity*> entities)
{
	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed)continue;
		addScript(entity);
	}


	m_systemManager->OnEntityAdded.Subscribe([this](Entity* entity)
		{
			entity->OnComponentAdded.Subscribe([this, entity](IComponent* component)
				{
					if (!entity->IsActive() || entity->isDestroyed) return;
					addScript(entity);
				});
			
		});


	m_systemManager->OnEntityRemoved.Subscribe([this](Entity* entity)
		{
			removeScript(entity);
		});
}

void CustomScriptsControllerSystem::update(std::vector<Entity*> entities, float deltaTime)
{


	for (const std::pair<Entity*,BaseScriptComponent*>&  scriptEntity:  m_listofScripts)
	{
		Entity* entity = scriptEntity.first;
		BaseScriptComponent* scriptComponent = scriptEntity.second;

		if (!entity->IsActive() || entity->isDestroyed) continue;

		if (!scriptComponent->m_isEnabled) continue;

		if (!scriptComponent->m_isStartInvoked)
		{
			scriptComponent->start();
			scriptComponent->m_isStartInvoked = true;
			continue;
		}

		
		scriptComponent->updateComponent();

	}
}

void CustomScriptsControllerSystem::render(std::vector<Entity*> entities)
{
	for (const std::pair<Entity*, BaseScriptComponent*>& scriptEntity : m_listofScripts)
	{
		Entity* entity = scriptEntity.first;
		BaseScriptComponent* scriptComponent = scriptEntity.second;

		if (!entity->IsActive() || entity->isDestroyed) continue;

		if (!scriptComponent->m_isEnabled) continue;

		scriptComponent->render();

	}
}

void CustomScriptsControllerSystem::cleanups()
{
	m_listofScripts.clear();
}

std::vector<BaseScriptComponent*> CustomScriptsControllerSystem::getScripts() const
{
	return std::vector<BaseScriptComponent*>();
}

void CustomScriptsControllerSystem::addScript(Entity* entity)
{
	BaseScriptComponent* script = (BaseScriptComponent*)entity->getComponent(ComponentType::SCRIPT_COMPONENT);

	if (!script) return;

	if (!ContainsScript(entity->getID()))
	{
		m_listofScripts.emplace_back(entity, script);
	}
}

void CustomScriptsControllerSystem::removeScript(Entity* entity)
{

	for (auto it = m_listofScripts.begin(); it != m_listofScripts.end(); ++it)
	{
		if ( it->first->getID() == entity->getID())
		{
			m_listofScripts.erase(it);
			return;
		}
	}
}

bool CustomScriptsControllerSystem::ContainsScript(EntityID id)
{
	for (std::pair < Entity*, BaseScriptComponent*> item :  m_listofScripts)
	{
		if (item.first->getID() == id);
		return true;
	}
	return false;
}
