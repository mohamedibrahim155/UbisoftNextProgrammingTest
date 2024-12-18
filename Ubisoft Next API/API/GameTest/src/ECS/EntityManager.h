#pragma once
#include "Entity.h"
#include <unordered_map>
#include "SystemManager.h"
class EntityManager
{
public:

	EntityManager(SystemManager* manager);
	~EntityManager() = default;
	Entity* CreateEntity();
	Entity* GetEntityByID(int ID);

	void DestroyEntity(int ID);
	void Clean();
	void SetSystemManager(SystemManager* manager);

private:

	int entityCount = 0;
	std::unordered_map <int, Entity*> listOfEntites;

	SystemManager* systemManager;
};

