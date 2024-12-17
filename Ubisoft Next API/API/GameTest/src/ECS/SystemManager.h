#pragma once
#include <unordered_map>
#include "System.h"
class SystemManager
{

public:

	void RegisterSystem(ISystem* system);
	void RemoveSystem(ISystem* system);

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);

	void CleanSystem();

	void Start();
	void UpdateSystems(float deltaTime);
	void Render();
private:

	int systemCount = 0;
	std::unordered_map<int, ISystem*> listOfSystems;

	std::vector<Entity*> listOfEntites;

};

