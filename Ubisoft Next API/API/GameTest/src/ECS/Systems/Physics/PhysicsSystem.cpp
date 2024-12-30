#include "stdafx.h"
#include "PhysicsSystem.h"
#include "../src/Utils/PhysicsUtils.h"
void PhysicsSystem::start(std::vector<Entity*> entities)
{

}

void PhysicsSystem::update(std::vector<Entity*> entities, float deltaTime)
{

	updateComponents(entities, deltaTime);
}

void PhysicsSystem::render(std::vector<Entity*> entities)
{
	for (Entity* entity : entities)
	{
		if (!entity->IsActive() || entity->isDestroyed) continue;

		Collider* collider = (Collider*)entity->GetComponent(ComponentType::COLLIDER_COMPONENT);

		if (collider == nullptr) continue;


		collider->render();
	}
}

void PhysicsSystem::cleanups()
{
}




void PhysicsSystem::updatePhysics(std::vector<Entity*> entities , float deltatime)
{
	timer += deltatime;

	if (timer >= FIXED_TIMESTEP)
	{
		updateComponents(entities,FIXED_TIMESTEP);
		timer = 0;
	}
}

void PhysicsSystem::updateComponents(std::vector<Entity*> entities, float deltatime)
{

	for (Entity* entity : entities)
	{

		if (!entity->IsActive() || entity->isDestroyed) continue;


		Transform* transform = &entity->transform;
		RigidBody* rb = (RigidBody*)entity->GetComponent(ComponentType::PHYSICS_COMPONENT);
		Collider* collider = (Collider*)entity->GetComponent(ComponentType::COLLIDER_COMPONENT);
		
		if (!rb || !transform) continue;
		if (!rb->isComponentEnabled || !collider->isComponentEnabled) continue;
		if (rb->GetbodyType() == eBodyType::STATIC) continue;


		
		float gravityAcceleration = GRAVITY * rb->GetGravityScale();

		Vector2 acceleration = rb->force / rb->GetMass();

		acceleration.y += gravityAcceleration;

		rb->velocity += acceleration * deltatime;

		collisionNormals.clear();
		collisionPoints.clear();

		for (Entity* otherEntity : entities)
		{
			if (entity == otherEntity) continue;

			Transform* otherTransform = &otherEntity->transform;
			RigidBody* otherRB = (RigidBody*)otherEntity->GetComponent(ComponentType::PHYSICS_COMPONENT);
			Collider* otherCollider = (Collider*)otherEntity->GetComponent(ComponentType::COLLIDER_COMPONENT);

			if (!otherCollider || !otherTransform || !collider) continue;
			if (!otherCollider->isComponentEnabled || !collider->isComponentEnabled) continue;
			if (otherCollider->IsUI() || collider->IsUI()) continue;

			std::vector<Vector2> perObjectCollisions;
			std::vector<Vector2> perObjectNormals;
			if (Physics::CheckCollision(collider, otherCollider, perObjectCollisions, perObjectNormals))
			{
				if (collider->IsTrigger() || otherCollider->IsTrigger())
				{
					continue;
				}

				collisionPoints.insert(collisionPoints.end(), perObjectCollisions.begin(), perObjectCollisions.end());
				collisionNormals.insert(collisionNormals.end(), perObjectNormals.begin(), perObjectNormals.end());

			}
			
			
		}
		if (!collisionNormals.empty())
		{
			Vector2 normal = Vector2::Zero();

			for (int i = 0; i < collisionNormals.size(); i++)
			{
				normal += collisionNormals[i].Normalize();
			}

			normal = normal / (float)(collisionNormals.size());

			Vector2 incident = rb->velocity;

			float dotProduct = Vector2::Dot(incident, normal);

			if (dotProduct < 0)
			{
				normal = normal * -1;

				dotProduct = -dotProduct;
			}

			float bounciness = 0.1f;

			Vector2 refllected = Vector2::Reflect(incident, normal);

			if (refllected.Magnitude() > 0.0001f)
			{
				rb->velocity = refllected * rb->bounciness;
			}
			else
			{
				rb->velocity = Vector2::Zero();
			}

		}

		transform->position += rb->velocity * deltatime;
	}
}


