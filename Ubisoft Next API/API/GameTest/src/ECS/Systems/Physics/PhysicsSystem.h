#pragma once
#include "../../System.h"
#include "../../Components/Collider/BoxCollider.h"
#include "../../Components/Collider/CircleCollider.h"
#include "../../Components/Collider/LineCollider.h"
#define GRAVITY (-9.81)
class PhysicsSystem : public ISystem
{
public:
	PhysicsSystem() : ISystem("PhysicsSystem", eSystemType::PHYSICS_SYSTEM) {};
	// Inherited via ISystem
	~PhysicsSystem() override = default;
	void Start(std::vector<Entity*> entities) override;
	void Update(std::vector<Entity*> entities, float deltaTime) override;
	void Render(std::vector<Entity*> entities) override;
	void Cleanups() override;

private:

	void UpdatePhysics(std::vector<Entity*> entities ,float deltatime);
	void UpdateComponents(std::vector<Entity*> entities, float deltatime);

	const float FIXED_TIMESTEP = 1 /60;
	float timer = 0;
};

