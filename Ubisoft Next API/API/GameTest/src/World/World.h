#pragma once
#include "src/ECS/SystemManager.h"
#include "src/ECS/EntityManager.h"
class World
{
public:
	World();

	~World()  = default;
	void Update(float deltaTime);
	void Render();
	void Clean();


private:

	SystemManager* systemManager;
	EntityManager* entityManager;

};

