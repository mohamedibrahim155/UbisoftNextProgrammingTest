#include "stdafx.h"
#include "CustomScriptsControllerSystem.h"
#include "../SystemManager.h"
void CustomScriptsControllerSystem::start(std::vector<Entity*> entities)
{
	subscribeEvents();
}

#pragma region Events calls


void CustomScriptsControllerSystem::subscribeEvents()
{
	m_systemManager->OnEntityAdded.Subscribe([this](Entity* entity)
		{
			handleOnEntityAdded(entity);

		});


	m_systemManager->OnEntityRemoved.Subscribe([this](Entity* entity)
		{
			removeScript(entity);
		});
}

void CustomScriptsControllerSystem::handleOnEntityAdded(Entity* entity)
{
	entity->OnComponentAdded.Subscribe([this, entity](IComponent* component)
		{
			handleOnComponentAdded(component, entity);

		});
}

void CustomScriptsControllerSystem::handleOnComponentAdded(IComponent* component, Entity* entity)
{
	if (component->getComponentType() == ComponentType::SCRIPT_COMPONENT)
	{
		addScript(entity);
	}
}
#pragma endregion


void CustomScriptsControllerSystem::update(std::vector<Entity*> entities, float deltaTime)
{

	for (auto& scriptEntity : m_listofScripts)
	{
		Entity* entity = scriptEntity.first;
		BaseScriptComponent* scriptComponent = scriptEntity.second;

		if (!entity->IsActive() || entity->isDestroyed || !scriptComponent)
			continue;

		if (!scriptComponent->m_isEnabled)
			continue;

		if (!scriptComponent->m_isStartInvoked)
		{
			scriptComponent->start();
			scriptComponent->m_isStartInvoked = true;
			continue;
		}

		scriptComponent->updateComponent();


		// If the scene has transitioned (indicated by m_isRefreshed 
		// being set to true during cleanup),
		// stop iterating over the current scripts.
		// New scripts will be iterated in the refreshed scene.
		if (m_isRefreshed)
		{
			m_isRefreshed = false;
			break;
		}
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
	m_isRefreshed = true;
}



std::vector<BaseScriptComponent*> CustomScriptsControllerSystem::getScripts() const
{
	std::vector<BaseScriptComponent*> scripts;
	for (std::pair<Entity*, BaseScriptComponent*> bs :  m_listofScripts)
	{
		scripts.push_back(bs.second);
	}

	return scripts;
}

void CustomScriptsControllerSystem::addScript(Entity* entity)
{
	BaseScriptComponent* script = (BaseScriptComponent*)entity->getComponent(ComponentType::SCRIPT_COMPONENT);

	if (!script) return;

	if (!containsScriptComponent(entity->getID()))
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

bool CustomScriptsControllerSystem::containsScriptComponent(EntityID id)
{
	for (std::pair < Entity*, BaseScriptComponent*> item :  m_listofScripts)
	{
		if (item.first->getID() == id)
			return true;
	}
	return false;
}
