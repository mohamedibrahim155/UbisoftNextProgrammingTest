#pragma once
#include "src/ECS/SystemManager.h"
#include "src/ECS/EntityManager.h"
class World
{
public:
	World();

	~World()  = default;
	 void start();
	void update(float deltaTime);
	void render();
	void clean();


private:

	SystemManager* systemManager;
	EntityManager* entityManager;

};

