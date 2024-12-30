#include "stdafx.h"
#include "RenderSystem.h"

void RenderSystem::Start(std::vector<Entity*> entities)
{
	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;
		{
			RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);
			
			if (renderComp == nullptr) continue;
			if (renderComp->IsUI()) continue;

			if (renderComp->isComponentEnabled && !renderComp->isStartInvoked)
			{
				renderComp->Start();
				renderComp->isStartInvoked = true;
			}
		}
	}

	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;

		ButtonRenderer* buttonRender= (ButtonRenderer*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (buttonRender == nullptr) continue;

		if (buttonRender->isComponentEnabled && !buttonRender->isStartInvoked)
		{
			buttonRender->Start();
			buttonRender->isStartInvoked = true;
		}
	}
}

void RenderSystem::Update(std::vector<Entity*> entities, float deltaTime)
{
	sortedEntities.clear();

	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;

		RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (renderComp == nullptr) continue;
		if (renderComp->IsUI()) continue;


		sortedEntities.emplace_back(renderComp->RenderOrder(), entity);

		renderComp->UpdateComponent();
	}

	std::sort(sortedEntities.begin(), sortedEntities.end(),
		[](const std::pair<int, Entity*>& a, const std::pair<int, Entity*>& b) {
			return a.first < b.first; // Ascending order of renderOrder
		});


	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;

		ButtonRenderer* buttonRender = (ButtonRenderer*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (buttonRender == nullptr) continue;

		buttonRender->UpdateComponent();
	}
}

void RenderSystem::Render(std::vector<Entity*> entities)
{
	for (const auto& pair : sortedEntities)
	{
		Entity* entity = pair.second;

		if (!entity->IsActive() || entity->isDestroyed) continue;
		RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (renderComp == nullptr) continue;
		if (renderComp->IsUI()) continue;

		renderComp->Render();
	}

	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;

		ButtonRenderer* buttonRender = (ButtonRenderer*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (buttonRender == nullptr) continue;

		buttonRender->Render();
	}
}

void RenderSystem::Cleanups()
{
	sortedEntities.clear();
}
