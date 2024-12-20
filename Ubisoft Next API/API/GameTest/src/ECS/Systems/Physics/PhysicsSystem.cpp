#include "stdafx.h"
#include "PhysicsSystem.h"
#include "../../Components/Rigidbody/RigidBody.h"
#include "../../Components/Collider/Collider.h"
void PhysicsSystem::Start(std::vector<Entity*> entities)
{
	for (Entity* entity : entities)
	{
		RigidBody* rigidbody = (RigidBody*)entity->GetComponent(ComponentType::PHYSICS_COMPONENT);

		if (rigidbody == nullptr)  continue;

		if (rigidbody->GetbodyType() == eBodyType::STATIC)
		{
			listOfStaticObjects.push_back(entity);
		}
		else
		{
			listOfDynamicsObjects.push_back(entity);
		}
	}
}

void PhysicsSystem::Update(std::vector<Entity*> entities, float deltaTime)
{
	UpdateComponents(deltaTime);

}

void PhysicsSystem::Render(std::vector<Entity*> entities)
{
	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;

		Collider* collider = (Collider*)entity->GetComponent(ComponentType::COLLIDER_COMPONENT);

		if (collider == nullptr) continue;


		collider->Render();
	}
}

void PhysicsSystem::Cleanups()
{
}

void PhysicsSystem::UpdatePhysics(float deltatime)
{
	timer += deltatime;

	if (timer > FIXED_TIMESTEP)
	{
		UpdateComponents(FIXED_TIMESTEP);
		timer = 0;
	}
}

void PhysicsSystem::UpdateComponents(float deltatime)
{
	for (Entity* staticEntity : listOfStaticObjects)
	{
		if (!staticEntity->IsActive() || staticEntity->isDestroyed) continue;




	}

	for (Entity* staticEntity : listOfStaticObjects)
	{
		if (!staticEntity->IsActive() || staticEntity->isDestroyed) continue;




	}

}
