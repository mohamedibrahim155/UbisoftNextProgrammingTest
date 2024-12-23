#include "stdafx.h"
#include "PhysicsSystem.h"
//#include "../../Components/Rigidbody/RigidBody.h"
//#include "../../Components/Collider/Collider.h"
#include "../src/Utils/PhysicsUtils.h"
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
	UpdateComponents(entities,deltaTime);
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

void PhysicsSystem::UpdatePhysics(std::vector<Entity*> entities , float deltatime)
{
	timer += deltatime;

	if (timer > FIXED_TIMESTEP)
	{
		UpdateComponents(entities,FIXED_TIMESTEP);
		timer = 0;
	}
}

void PhysicsSystem::UpdateComponents(std::vector<Entity*> entities, float deltatime)
{

	for (Entity* entity : entities)
	{

		if (!entity->IsActive() || entity->isDestroyed) continue;


		Transform* transform = &entity->transform;
		RigidBody* rb = (RigidBody*)entity->GetComponent(ComponentType::PHYSICS_COMPONENT);
		Collider* collider = (Collider*)entity->GetComponent(ComponentType::COLLIDER_COMPONENT);
		
		if (!rb || !transform) continue;
		if (rb->GetbodyType() == eBodyType::STATIC) continue;


		
		float gravityAcceleration = GRAVITY * rb->GetGravityScale();

		Vector2 acceleration = rb->force / rb->GetMass();

		acceleration.y += gravityAcceleration;

		rb->velocity += acceleration * deltatime;


		// Setting to object
		transform->position += rb->velocity * deltatime;



		for (Entity* otherEntity : entities)
		{
			if (entity == otherEntity) continue;

			Transform* otherTransform = &otherEntity->transform;
			RigidBody* otherRB = (RigidBody*)otherEntity->GetComponent(ComponentType::PHYSICS_COMPONENT);
			Collider* otherColldier = (Collider*)otherEntity->GetComponent(ComponentType::COLLIDER_COMPONENT);

			if (!otherColldier || !otherTransform || !collider) continue;


			// Check Collision

			if (Physics::CheckCollision(collider, otherColldier))
			{


				Physics::ResolveCollision(rb, otherRB, transform, otherTransform);
			}
		}


		rb->force = { 0.0f, 0.0f };
	}
}
