#pragma once
#include "src/ECS/SystemManager.h"
#include "src/ECS/EntityManager.h"
class World
{
public:
	World();

	~World()  = default;
	 void start();
	void Update(float deltaTime);
	void render();
	void Clean();


private:

	SystemManager* systemManager;
	EntityManager* entityManager;

};

