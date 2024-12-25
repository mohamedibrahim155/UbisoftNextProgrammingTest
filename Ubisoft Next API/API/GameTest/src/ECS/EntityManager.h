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
	Entity* CreateEntityFromCopy(Entity* entity);
	Entity* GetEntityByID(EntityID ID);

	void AddEntity(Entity* entity);
	void RemoveEntity(EntityID ID);
	void Clean();

	inline unsigned int GetEntitiesCount() { return entityCount;  }
	inline SystemManager* GetSystemManager() { return systemManager; }
private:

	int entityCount = 0;
	std::unordered_map <EntityID, Entity*> entitiesMap;
	std::vector<Entity*> listOfEntites;


	SystemManager* systemManager;
};

