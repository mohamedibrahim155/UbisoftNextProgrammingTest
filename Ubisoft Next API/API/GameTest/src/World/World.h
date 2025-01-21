///////////////////////////////////////////////////////////////////////////////
// Filename: World.h
// world renders to the assets of world
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "src/ECS/SystemManager.h"
#include "src/ECS/EntityManager.h"
class World
{
public:
	World();

	~World()  = default;

	//Inits world objects
	 void start();
	 //updates world's object everyframe
	void update(float deltaTime);

	//renders world's object everyframe
	void render();

	//cleans object while shutdown
	void clean();


private:

	//Managers
	SystemManager* systemManager;
	EntityManager* entityManager;

};

