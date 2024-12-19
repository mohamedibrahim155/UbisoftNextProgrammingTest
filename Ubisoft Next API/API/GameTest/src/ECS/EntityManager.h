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
	Entity* GetEntityByID(EntityID ID);

	void AddEntity(Entity* entity);
	void RemoveEntity(EntityID ID);
	void Clean();

	inline unsigned int GetEntitiesCount() { return entityCount;  }
private:

	int entityCount = 0;
	std::unordered_map <EntityID, Entity*> entitiesMap;

	SystemManager* systemManager;
};

