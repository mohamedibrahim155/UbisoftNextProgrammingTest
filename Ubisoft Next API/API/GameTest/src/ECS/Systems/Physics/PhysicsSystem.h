#pragma once
#include "../../System.h"
#include "../../Components/Collider/BoxCollider.h"
#include "../../Components/Collider/CircleCollider.h"
#define GRAVITY (-9.81)
class PhysicsSystem : public ISystem
{
public:
	PhysicsSystem() : ISystem("PhysicsSystem") {};
	// Inherited via ISystem
	void Start(std::vector<Entity*> entities) override;
	void Update(std::vector<Entity*> entities, float deltaTime) override;
	void Render(std::vector<Entity*> entities) override;
	void Cleanups() override;

private:

	std::vector<Entity*> listOfStaticObjects;
	std::vector<Entity*> listOfDynamicsObjects;

	void UpdatePhysics(std::vector<Entity*> entities ,float deltatime);
	void UpdateComponents(std::vector<Entity*> entities, float deltatime);

	const float FIXED_TIMESTEP = 1 /60;
	float timer = 0;
};

