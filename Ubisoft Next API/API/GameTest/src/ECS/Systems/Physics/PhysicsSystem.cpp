#include "stdafx.h"
#include "PhysicsSystem.h"
#include "../src/Utils/PhysicsUtils.h"
#include "../../SystemManager.h"
#include <algorithm>

std::vector<Collider*> PhysicsSystem::listOfColliders;

std::vector<Collider*> PhysicsSystem::getWorldColliders()
{
	return listOfColliders;
}
void PhysicsSystem::start(std::vector<Entity*> entities)
{
	listOfColliders.clear();

	for ( Entity* entity : entities )
	{
		addPhysicsObject(entity);
	}

	subscribeEvents();
}

void PhysicsSystem::subscribeEvents()
{
	m_systemManager->OnEntityAdded.Subscribe([this](Entity* entity)
		{
			entity->OnComponentAdded.Subscribe([this, entity](IComponent* component)
				{
					if (component->getComponentType() ==ComponentType::COLLIDER_COMPONENT || component->getComponentType() == ComponentType::PHYSICS_COMPONENT)
					{
						addPhysicsObject(entity);
					}

				});
		});

	m_systemManager->OnEntityRemoved.Subscribe([this](Entity* entity)
		{
			removePhysicsObject(entity);
		});
}

void PhysicsSystem::update(std::vector<Entity*> entities, float deltaTime)
{

	updatePhysics(entities, deltaTime);
}

void PhysicsSystem::render(std::vector<Entity*> entities)
{
	
	for (const std::pair<EntityID, PhysicsEntity>& object : staticObjectsMap)
	{
		if (!object.second.collider) continue;

			object.second.collider->render();
		
	}

	for (const std::pair<EntityID, PhysicsEntity>& object : physicsObjectsMap)
	{
		if (!object.second.collider) continue;
		
		object.second.collider->render();
		
	}
}

void PhysicsSystem::cleanups()
{
	staticObjectsMap.clear();
	physicsObjectsMap.clear();
	listOfColliders.clear();
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
		for (auto& physicsObject : physicsObjectsMap)
		{
			Entity* entity = physicsObject.second.entity;

			if (!entity || !entity->IsActive() || entity->isDestroyed) continue;

			Transform* transform = &entity->transform;
			RigidBody* rb = physicsObject.second.rb;
			Collider* collider = physicsObject.second.collider;

			if (!transform || !rb || !collider) continue;
			if (!rb->m_isEnabled) continue;
			if (rb->GetbodyType() == eBodyType::STATIC) continue;



			Vector2 acceleration = rb->force / rb->GetMass();
			acceleration.y += GRAVITY * rb->GetGravityScale();
			rb->velocity += acceleration * deltatime;


			collisionNormals.clear();
			collisionPoints.clear();

			//StaticObjects collisions
			for ( const std::pair<EntityID, PhysicsEntity>&  staticObj : staticObjectsMap) 
			{
				Collider* otherCollider = staticObj.second.collider;

				if (!otherCollider->m_isEnabled || !collider->m_isEnabled) continue;
				if (otherCollider->IsUI() || collider->IsUI()) continue;

				if (Physics::CheckCollision(collider, otherCollider, collisionPoints, collisionNormals))
				{
					if (collider->IsTrigger()  || otherCollider->IsTrigger())
					{
						continue;
					}
					resolveCollisions(rb, collisionNormals);
				}
			}

			//DynamicObjects
			for (const std::pair<EntityID, PhysicsEntity>&  otherObj : physicsObjectsMap)
			{

				if (physicsObject.first == otherObj.first) continue;

				Collider* otherCollider = otherObj.second.collider;
				
				if (!otherCollider->m_isEnabled || !collider->m_isEnabled) continue;
				if (otherCollider->IsUI() || collider->IsUI()) continue;


				if (Physics::CheckCollision(collider, otherCollider, collisionPoints, collisionNormals))
				{
					
					if (collider->IsTrigger() || otherCollider->IsTrigger())
					{
						continue;
					}

					resolveCollisions(rb, collisionNormals);
				}
			}

			// Update position
			transform->position += rb->velocity * deltatime;
		}

		
}


void PhysicsSystem::addPhysicsObject(Entity* entity)
{
	Collider* collider = (Collider*)entity->getComponent(ComponentType::COLLIDER_COMPONENT);
	RigidBody* rb = (RigidBody*)entity->getComponent(ComponentType::PHYSICS_COMPONENT);
	
	if (!rb && !collider) return;


	EntityID id = entity->getID();
	PhysicsEntity physicsEntity{ entity, collider, rb };

	if (rb && rb->GetbodyType() == eBodyType::STATIC)
	{
		staticObjectsMap[id] = physicsEntity;
	}
	else
	{
		physicsObjectsMap[id] = physicsEntity;
	}


	if (collider && !ContainsCollider(collider)) 
		listOfColliders.push_back(collider);

}

void PhysicsSystem::removePhysicsObject(Entity* entity)
{
	removeStaticObject(entity);
	removeDynamicObject(entity);
}

void PhysicsSystem::removeDynamicObject(Entity* entity)
{

	physicsObjectsMap.erase(entity->getID());
	
}

void PhysicsSystem::removeStaticObject(Entity* entity)
{
	staticObjectsMap.erase(entity->getID());
}


void PhysicsSystem::resolveCollisions(RigidBody* rb, std::vector<Vector2>& collisionNormals)
{
	if (collisionNormals.empty()) return;

	Vector2 normal = computeNormals(collisionNormals);

	Vector2 incident = rb->velocity;
	float dotProduct = Vector2::Dot(incident, normal);

	rb->velocity = (dotProduct < 0) ? 
		  Vector2::Reflect(incident, normal) * -rb->bounciness : Vector2::Zero();
}

Vector2 PhysicsSystem::computeNormals(std::vector<Vector2>& collisionNormals)
{
	Vector2 normal = Vector2::Zero();
	for (const auto& n : collisionNormals)
	{
		normal += Vector2::Normalize(n);
	}
	normal = normal / static_cast<float>(collisionNormals.size());

	return normal;
}

bool PhysicsSystem::ContainsCollider(Collider* collider)
{
	for (Collider* c  : listOfColliders )
	{
		if (c == collider)
		{
			return true;
		}
	}

	return false;
}


