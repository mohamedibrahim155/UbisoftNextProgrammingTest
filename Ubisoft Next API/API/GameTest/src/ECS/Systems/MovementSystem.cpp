#include "stdafx.h"
#include "MovementSystem.h"

void MovementSystem::start(std::vector<Entity*> entities)
{
	
}

void MovementSystem::update(std::vector<Entity*> entities, float deltaTime)
{
	for (Entity* entity : entities)
	{
		
		if (!entity->IsActive() || entity->isDestroyed) continue;
		Transform* transform = &entity->transform;

		if (transform == nullptr) continue;


		Vector3 position = transform->position;
		float rotation = transform->rotation;
		Vector2 scale = transform->scale;

		

		entity->setPosition(position);
		entity->setRotation(rotation);
		entity->setScale(scale);
	}

	
}

void MovementSystem::render(std::vector<Entity*> entities)
{
}

void MovementSystem::cleanups()
{
}
