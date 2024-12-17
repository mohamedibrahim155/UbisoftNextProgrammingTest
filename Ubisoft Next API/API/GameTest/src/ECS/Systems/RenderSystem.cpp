#include "stdafx.h"
#include "RenderSystem.h"

void RenderSystem::Start()
{
}

void RenderSystem::Update(std::vector<Entity*> entities, float deltaTime)
{

	for (Entity* entity : entities)
	{
		RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (renderComp != nullptr)
		{
			renderComp->UpdateComponent();
		}
	}
}

void RenderSystem::Render(std::vector<Entity*> entities)
{
	for (Entity* entity : entities)
	{
		RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (renderComp != nullptr)
		{
			renderComp->Render();
		}
	}
}

void RenderSystem::Cleanups()
{
}
