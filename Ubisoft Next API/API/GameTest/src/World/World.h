#pragma once
#include "src/ECS/SystemManager.h"
#include "src/ECS/EntityManager.h"
class World
{
public:
	World();

	~World()  = default;
	 void Start();
	void Update(float deltaTime);
	void Render();
	void Clean();


private:

	SystemManager* systemManager;
	EntityManager* entityManager;

};

