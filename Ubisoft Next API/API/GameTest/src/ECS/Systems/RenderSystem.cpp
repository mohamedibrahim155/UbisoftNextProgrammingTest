#include "stdafx.h"
#include "RenderSystem.h"

void RenderSystem::Start(std::vector<Entity*> entities)
{
	
}

void RenderSystem::Update(std::vector<Entity*> entities, float deltaTime)
{

	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;

		RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (renderComp == nullptr) continue;
		
		renderComp->UpdateComponent();
	}
}

void RenderSystem::Render(std::vector<Entity*> entities)
{
	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;
		RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (renderComp == nullptr) continue;

		renderComp->Render();
	}
}

void RenderSystem::Cleanups()
{
}
