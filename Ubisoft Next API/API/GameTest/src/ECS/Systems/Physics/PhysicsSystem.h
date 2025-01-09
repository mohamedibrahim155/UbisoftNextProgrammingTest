#pragma once
#include "../../System.h"
#include "../../Components/Collider/BoxCollider.h"
#include "../../Components/Collider/CircleCollider.h"
#include "../../Components/Collider/LineCollider.h"
#include "../../Components/Rigidbody/RigidBody.h"
#define GRAVITY (-9.81)


struct PhysicsEntity
{
	Entity* entity;
	Collider* collider;
	RigidBody* rb;

	PhysicsEntity() = default;

	PhysicsEntity(Entity* entity, Collider* collider,RigidBody* rb):
	entity(entity),
	collider(collider), 
	rb(rb)
	{}
};

class PhysicsSystem : public ISystem
{
public:
	PhysicsSystem() : ISystem("PhysicsSystem", eSystemType::PHYSICS_SYSTEM) {};
	// Inherited via ISystem
	~PhysicsSystem() override = default;
	void start(std::vector<Entity*> entities) override;
	void update(std::vector<Entity*> entities, float deltaTime) override;
	void render(std::vector<Entity*> entities, bool isDebugVisible) override;
	void cleanups() override;

	static std::vector<Collider*> getWorldColliders();

private:

	void updatePhysics(std::vector<Entity*> entities ,float deltatime);
	void updateComponents(std::vector<Entity*> entities, float deltatime);
	void subscribeEvents();

	void addPhysicsObject(Entity* entity);
	void removePhysicsObject(Entity* entity);

	void resolveCollisions(RigidBody* rb, std::vector<Vector2>& collisionNormals);

	Vector2 computeNormals(std::vector<Vector2>& collisionNormals);

	bool ContainsCollider(Collider* collider);

	const float FIXED_TIMESTEP = 1.0f / 60.0f;
	float timer = 0;

	std::vector<Vector2> collisionPoints;
	std::vector<Vector2> collisionNormals;

    static std::vector<Collider*> m_globalColliders;

	std::unordered_map<EntityID, PhysicsEntity> staticObjectsMap;
	std::unordered_map<EntityID, PhysicsEntity> physicsObjectsMap;

	

};

