#include "stdafx.h"
#include "MovementSystem.h"
#include "../src/ECS/SystemManager.h"
#include "../src/InputManager/InputManager.h"

void MovementSystem::start(std::vector<Entity*> entities)
{
	
}

void MovementSystem::update(std::vector<Entity*> entities, float deltaTime)
{

	if (!Camera::mainCamera()) return;

	updateCameraInputs();	

	for (Entity* entity : entities)
	{
		
		if (!entity->IsActive() || entity->isDestroyed) continue;
		Transform* transform = &entity->transform;

		if (transform == nullptr) continue;



		Vector3 position = transform->position;
		float rotation = transform->rotation;
		Vector2 scale = transform->scale;

	
		// Adjust position based on the camera (fake the camera effect)
	//	Vector3 adjustedPosition = (worldPosition + worldOrigin) - Camera::mainCamera()->getEntity()->transform.position;

		// Update the entity's transform position with the adjusted position

		if (entity == Camera::mainCamera()->getEntity()) continue;

		entity->setPosition(position, Camera::mainCamera()->getEntity()->transform.position);
		entity->setRotation(rotation);
		entity->setScale(scale);

	}

	
}

void MovementSystem::render(std::vector<Entity*> entities, bool isDebugVisible)
{
}

void MovementSystem::cleanups()
{
}

void MovementSystem::updateCameraInputs()
{
	if (!m_systemManager->IsDebug()) return;

	if (InputManager::GetInstance().getKey('W'))
	{
		Camera::mainCamera()->getEntity()->transform.position.y += 1;
	}
	if (InputManager::GetInstance().getKey('S'))
	{
		Camera::mainCamera()->getEntity()->transform.position.y -= 1;
	}
	if (InputManager::GetInstance().getKey('A'))
	{
		Camera::mainCamera()->getEntity()->transform.position.x -= 1;
	}
	if (InputManager::GetInstance().getKey('D'))
	{
		Camera::mainCamera()->getEntity()->transform.position.x += 1;
	}
}
