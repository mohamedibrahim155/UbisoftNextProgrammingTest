#include "stdafx.h"
#include "MovementSystem.h"

void MovementSystem::Start()
{
}

void MovementSystem::Update(std::vector<Entity*> entities, float deltaTime)
{
	for (Entity* entity : entities)
	{
		Transform* transform = &entity->transform;
		RenderComponent* renderComp = (RenderComponent*)entity->GetComponent(ComponentType::RENDER_COMPONENT);

		if (renderComp == nullptr && transform == nullptr) continue;


		Vector3 position = entity->transform.position;
		Vector2 scale = transform->scale;

		

		entity->SetPosition(position);
	}
}

void MovementSystem::Render(std::vector<Entity*> entities)
{
}

void MovementSystem::Cleanups()
{
}
