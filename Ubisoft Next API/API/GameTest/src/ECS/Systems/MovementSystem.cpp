#include "stdafx.h"
#include "MovementSystem.h"

void MovementSystem::Start(std::vector<Entity*> entities)
{
	
}

void MovementSystem::Update(std::vector<Entity*> entities, float deltaTime)
{
	for (Entity* entity : entities)
	{
		
		if (!entity->IsActive() || entity->isDestroyed) continue;
		Transform* transform = &entity->transform;

		if (transform == nullptr) continue;


		Vector3 position = transform->position;
		float rotation = transform->rotation;
		Vector2 scale = transform->scale;

		

		entity->SetPosition(position);
		entity->SetRotation(rotation);
		entity->SetScale(scale);
	}

	
}

void MovementSystem::Render(std::vector<Entity*> entities)
{
}

void MovementSystem::Cleanups()
{
}
