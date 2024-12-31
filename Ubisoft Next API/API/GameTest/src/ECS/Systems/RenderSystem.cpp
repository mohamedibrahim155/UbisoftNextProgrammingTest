#include "stdafx.h"
#include "RenderSystem.h"
#include "../SystemManager.h"
void RenderSystem::start(std::vector<Entity*> entities)
{

	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;
		{
			addEntityToRenders(entity);
		}
	}

	SubscribeEvents();
}

void RenderSystem::update(std::vector<Entity*> entities, float deltaTime)
{
	


	//Updates UI
	for (RenderEntity* renderEntity : listOfUIRenderer)
	{
		if (!renderEntity->entity->IsActive() || renderEntity->entity->isDestroyed) continue;

		renderEntity->component->updateComponent();
	}


	sortedSprites.clear();
	// updates sprites
	for (RenderEntity* renderEntity : listOfSpriteRenderers )
	{
		if (!renderEntity->entity->IsActive() || renderEntity->entity->isDestroyed) continue;

		sortedSprites.emplace_back(renderEntity->component->renderOrder(), renderEntity);

		renderEntity->component->updateComponent();
	}

	std::sort(sortedSprites.begin(), sortedSprites.end(),
		[](const std::pair<int, RenderEntity*>& a, const std::pair<int, RenderEntity*>& b) {
			return a.first < b.first; // Ascending order of renderOrder
		});

	
}

void RenderSystem::render(std::vector<Entity*> entities)
{
	
	// Renders UI's
	for (RenderEntity* renderEntity : listOfUIRenderer)
	{
		if (!renderEntity->entity->IsActive() || renderEntity->entity->isDestroyed) continue;

		

		renderEntity->component->render();
	}

	// Renders sprites
	for (const auto& pair : sortedSprites)
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
	sortedSprites.clear();
	listOfSpriteRenderers.clear();
	listOfUIRenderer.clear();
}

void RenderSystem::SubscribeEvents()
{
	// If Instantiated on runtime, subscribing when ADDED
	systemManager->OnEntityAdded.Subscribe([this](Entity* entity)
		{
			//Subscribing when the relvant component added to this entity
			HandleOnEntityAdded(entity);
			

		});

	systemManager->OnEntityRemoved.Subscribe([&](Entity* entity)
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
	for (auto it = listOfUIRenderer.begin(); it != listOfUIRenderer.end(); ++it)
	{
		if ((*it)->ID == entity->getID())
		{
			delete* it; 
			listOfUIRenderer.erase(it); 
			return;
		}
	}

	// Removes Sprite 
	for (auto it = listOfSpriteRenderers.begin(); it != listOfSpriteRenderers.end(); ++it)
	{
		if ((*it)->ID == entity->getID())
		{
			delete* it;
			listOfSpriteRenderers.erase(it);
			return;
		}
	}


}

void RenderSystem::addEntityToRenders(Entity* entity)
{
	RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

	if (!renderComp) return;

	RenderEntity* renderEntity = new  RenderEntity(entity->getID(), entity, renderComp);

	if (renderComp->IsUI())
	{
		listOfUIRenderer.push_back(renderEntity);
	}
	else
	{
		listOfSpriteRenderers.push_back(renderEntity);
	}

	if (!renderComp->isStartInvoked)
	{
		renderComp->start();
		renderComp->isStartInvoked = true;
	}
}




