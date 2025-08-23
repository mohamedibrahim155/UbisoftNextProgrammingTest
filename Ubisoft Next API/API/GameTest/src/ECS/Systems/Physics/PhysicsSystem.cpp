#include "stdafx.h"
#include "PhysicsSystem.h"
#include "../src/Utils/PhysicsUtils.h"
#include "../../SystemManager.h"
#include <algorithm>

std::vector<Collider*> PhysicsSystem::m_globalColliders;

std::vector<Collider*> PhysicsSystem::getWorldColliders()
{
	return m_globalColliders;
}


void PhysicsSystem::subscribeEvents()
{
	m_systemManager->OnEntityAdded.Subscribe([this](Entity* entity)
		{
			entity->OnComponentAdded.Subscribe([this, entity](IComponent* component)
				{
					if (component->getComponentType() ==eComponentType::COLLIDER_COMPONENT || component->getComponentType() == eComponentType::PHYSICS_COMPONENT)
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

void PhysicsSystem::start()
{
	m_globalColliders.clear();
	subscribeEvents();
}

#pragma region Physics Update

void PhysicsSystem::update(std::vector<Entity*> entities, float deltaTime)
{

	updatePhysics(entities, deltaTime);
}
void PhysicsSystem::updatePhysics(std::vector<Entity*> entities, float deltatime)
{
	timer += deltatime;

	if (timer >= FIXED_TIMESTEP)
	{
		updateComponents(entities, FIXED_TIMESTEP);
		timer -= FIXED_TIMESTEP;
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

		if (!rb->m_isStartInvoked && !collider->m_isStartInvoked)
		{
			rb->start();
			rb->m_isStartInvoked = true;
			collider->start();
			collider->m_isStartInvoked = true;
			continue;
		}

		if (rb->getbodyType() == eBodyType::STATIC) continue;



		Vector2 acceleration = rb->force / rb->getMass();
		acceleration.y += GRAVITY * rb->getGravityScale();
		rb->velocity += acceleration * deltatime;

		Vector2 dragForce = rb->velocity * -rb->getDrag(); // Drag opposes velocity
		rb->velocity += dragForce * deltatime;

		collisionNormals.clear();
		collisionPoints.clear();


#pragma region Dynamic Collisions



		//DynamicObjects collisions
		for (const std::pair<EntityID, PhysicsEntity>& otherObj : physicsObjectsMap)
		{

			if (physicsObject.first == otherObj.first) continue;

			Collider* otherCollider = otherObj.second.collider;

			if (!otherCollider->m_isEnabled || !collider->m_isEnabled) continue;
			if (otherCollider->IsUI() || collider->IsUI()) continue;

			std::vector<Vector2> perObjectCollisions;
			std::vector<Vector2> perObjectNormals;

			if (Physics::CheckCollision(collider, otherCollider, perObjectCollisions, perObjectNormals))
			{
				collisionPoints.insert(collisionPoints.end(), perObjectCollisions.begin(), perObjectCollisions.end());
				collisionNormals.insert(collisionNormals.end(), perObjectNormals.begin(), perObjectNormals.end());


				if (collider->IsTrigger() || otherCollider->IsTrigger())
				{
					//trigger enter
					if (!collider->isTriggering && !otherCollider->isTriggering)
					{
						collider->OnTriggerEnter.Invoke(otherCollider);
						otherCollider->OnTriggerEnter.Invoke(collider);
						
						collider->isTriggering = true;
						otherCollider->isTriggering = true;
					}

					// trigger stay
						collider->OnTrigger.Invoke(otherCollider);
						otherCollider->OnTrigger.Invoke(collider);
				
						continue;
				}

				//On collision Enter
				if (!collider->isColliding && !otherCollider->isColliding)
				{
					collider->OnCollisionEnter.Invoke(otherCollider);
					otherCollider->OnCollisionEnter.Invoke(collider);

					collider->isColliding = true;
					otherCollider->isColliding = true;
				}

				// On Collision Stay
				collider->OnCollision.Invoke(otherCollider);
				otherCollider->OnCollision.Invoke(collider);

				resolveCollisions(rb);

			}
			else
			{
				// Ontrigger Exit
				if (collider->IsTrigger() || otherCollider->IsTrigger())
				{
					if (collider->isTriggering && otherCollider->isTriggering)
					{
						collider->OnTriggerExit.Invoke(otherCollider);
						otherCollider->OnTriggerExit.Invoke(collider);

						collider->isTriggering = false;
						otherCollider->isTriggering = false;
					}
				}

				//On Collision Exit
				if (collider->isColliding && otherCollider->isColliding)
				{
					collider->OnCollisionExit.Invoke(otherCollider);
					otherCollider->OnCollisionExit.Invoke(collider);

					collider->isColliding = false;
					otherCollider->isColliding = false;
				}
			}




		}

		
#pragma endregion


		// Update position
		transform->position += rb->velocity * deltatime;
	}


}

void PhysicsSystem::render(bool isDebugVisible)
{
	

	for (const std::pair<EntityID, PhysicsEntity>& object : physicsObjectsMap)
	{
		if (!object.second.collider) continue;
		
		object.second.collider->render(isDebugVisible);
		
	}
}
#pragma endregion

void PhysicsSystem::cleanups()
{
	//clears all list
	physicsObjectsMap.clear();
	m_globalColliders.clear();
}

void PhysicsSystem::addPhysicsObject(Entity* entity)
{
	Collider* collider = (Collider*)entity->getComponent(eComponentType::COLLIDER_COMPONENT);
	RigidBody* rb = (RigidBody*)entity->getComponent(eComponentType::PHYSICS_COMPONENT);
	
	if (rb == nullptr || collider == nullptr)
	{
		return;
	}


	EntityID id = entity->getID();
	PhysicsEntity physicsEntity{ entity, collider, rb };

	physicsObjectsMap[id] = physicsEntity;

	if (collider && !isContainsCollider(collider)) 
		m_globalColliders.push_back(collider);

}

void PhysicsSystem::removePhysicsObject(Entity* entity)
{
	EntityID ID = entity->getID();
	physicsObjectsMap.erase(ID);
}

bool PhysicsSystem::isContainsCollider(Collider* collider)
{
	for (Collider* c : m_globalColliders)
	{
		if (c == collider)
		{
			return true;
		}
	}

	return false;
}

#pragma region Collision

Vector2 PhysicsSystem::computeNormals(std::vector<Vector2>& collisionNormals)
{
	Vector2 normal = Vector2::Zero();
	for (const auto& n : collisionNormals)
	{
	
		normal = normal + n;
	}
	normal = normal / static_cast<float>(collisionNormals.size());

	return normal;
}

void PhysicsSystem::resolveCollisions(RigidBody* rb)
{
	if (collisionNormals.size() > 0)
	{
		Vector2 normal = computeNormals(collisionNormals);

		normal = normal.Normalize();

		Vector2 incident = rb->velocity;

		float dotProduct = Vector2::Dot(incident, normal);

		if (dotProduct < 0)
		{
			normal = normal * -1;
			dotProduct = -dotProduct;
		}

		Vector2 reflected = Vector2::Reflect(incident, normal);


		float distancedReflected = reflected.Magnitude();
		if (distancedReflected > 0.001f)
		{
			rb->velocity = reflected * rb->bounciness;
		}
		else
		{
			rb->velocity = Vector2::Zero();
		}

	}
}



#pragma endregion





