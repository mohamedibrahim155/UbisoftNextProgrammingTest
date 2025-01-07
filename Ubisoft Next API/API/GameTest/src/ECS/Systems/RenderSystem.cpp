#include "stdafx.h"
#include "RenderSystem.h"
#include "../SystemManager.h"
void RenderSystem::start(std::vector<Entity*> entities)
{

	for (Entity* entity : entities)
	{
		//if (!entity->IsActive() || entity->isDestroyed) continue;
		{
			addEntityToRenders(entity);
		}
	}

	SubscribeEvents();
}

void RenderSystem::update(std::vector<Entity*> entities, float deltaTime)
{
	


	//Updates UI
	for (RenderEntity* renderEntity : m_listOfUIRenderer)
	{
		if (!renderEntity->entity->IsActive() || renderEntity->entity->isDestroyed) continue;

		renderEntity->component->updateComponent();
	}


	m_sortedSprites.clear();
	// updates sprites
	for (RenderEntity* renderEntity : m_listOfSpriteRenderers )
	{
		if (!renderEntity->entity->IsActive() || renderEntity->entity->isDestroyed) continue;

		m_sortedSprites.emplace_back(renderEntity->component->renderOrder(), renderEntity);

		renderEntity->component->updateComponent();
	}

	std::sort(m_sortedSprites.begin(), m_sortedSprites.end(),
		[](const std::pair<int, RenderEntity*>& a, const std::pair<int, RenderEntity*>& b) {
			return a.first < b.first; // Ascending order of renderOrder
		});

	
}

void RenderSystem::render(std::vector<Entity*> entities)
{
	
	// Renders UI's
	for (RenderEntity* renderEntity : m_listOfUIRenderer)
	{
		if (!renderEntity->entity->IsActive() || renderEntity->entity->isDestroyed) continue;

		

		renderEntity->component->render();
	}

	// Renders sprites
	for (const auto& pair : m_sortedSprites)
	{
		RenderEntity* renderEntity = pair.second;
		RenderComponent* renderComp = renderEntity->component;

		if (!renderEntity->entity->IsActive() || renderEntity->entity->isDestroyed) continue;
	//	RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (renderComp == nullptr) continue;

		renderComp->render();
	}
}

void RenderSystem::cleanups()
{
	m_sortedSprites.clear();
	m_listOfSpriteRenderers.clear();
	m_listOfUIRenderer.clear();
}

void RenderSystem::SubscribeEvents()
{
	// If Instantiated on runtime, subscribing when ADDED
	m_systemManager->OnEntityAdded.Subscribe([this](Entity* entity)
		{
			//Subscribing when the relvant component added to this entity
			HandleOnEntityAdded(entity);
			

		});

	m_systemManager->OnEntityRemoved.Subscribe([this](Entity* entity)
		{
			removeEntityFromRenders(entity);
		});
}

void RenderSystem::HandleOnEntityAdded(Entity* entity)
{
	entity->OnComponentAdded.Subscribe([this, entity](IComponent* component)
		{
			if (component->getComponentType() == ComponentType::RENDER_COMPONENT)
			{
				addEntityToRenders(entity);
			}
		});
}

void RenderSystem::removeEntityFromRenders(Entity* entity)
{
	//Removes UI's
	for (auto it = m_listOfUIRenderer.begin(); it != m_listOfUIRenderer.end(); ++it)
	{
		if ((*it)->ID == entity->getID())
		{
			delete* it; 
			m_listOfUIRenderer.erase(it); 
			return;
		}
	}

	// Removes Sprite 
	for (auto it = m_listOfSpriteRenderers.begin(); it != m_listOfSpriteRenderers.end(); ++it)
	{
		if ((*it)->ID == entity->getID())
		{
			delete* it;
			m_listOfSpriteRenderers.erase(it);
			return;
		}
	}


}

void RenderSystem::addEntityToRenders(Entity* entity)
{
	RenderComponent* renderComp = (RenderComponent*)entity->getComponent(ComponentType::RENDER_COMPONENT);

	if (!renderComp) return;

	RenderEntity* renderEntity = new  RenderEntity(entity->getID(), entity, renderComp);

	if (renderComp->IsUI())
	{
		m_listOfUIRenderer.push_back(renderEntity);
	}
	else
	{
		m_listOfSpriteRenderers.push_back(renderEntity);
	}

	if (!renderComp->m_isStartInvoked)
	{
		renderComp->start();
		renderComp->m_isStartInvoked = true;
	}
}




