#include "stdafx.h"
#include "RenderSystem.h"

void RenderSystem::Start(std::vector<Entity*> entities)
{
	
}

void RenderSystem::Update(std::vector<Entity*> entities, float deltaTime)
{
	sortedEntities.clear();

	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;

		RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (renderComp == nullptr) continue;


		sortedEntities.emplace_back(renderComp->RenderOrder(), entity);

		renderComp->UpdateComponent();
	}

	std::sort(sortedEntities.begin(), sortedEntities.end(),
		[](const std::pair<int, Entity*>& a, const std::pair<int, Entity*>& b) {
			return a.first < b.first; // Ascending order of renderOrder
		});
}

void RenderSystem::Render(std::vector<Entity*> entities)
{
	for (const auto& pair : sortedEntities)
	{
		Entity* entity = pair.second;

		if (!entity->IsActive() || entity->isDestroyed) continue;
		RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (renderComp == nullptr) continue;

		renderComp->Render();
	}
}

void RenderSystem::Cleanups()
{
	sortedEntities.clear();
}
