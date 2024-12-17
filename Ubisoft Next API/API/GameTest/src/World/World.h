#pragma once
#include "src/ECS/SystemManager.h"
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

};

