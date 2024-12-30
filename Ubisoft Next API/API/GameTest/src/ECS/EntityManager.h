#pragma once
#include "Entity.h"
#include <unordered_map>
#include "SystemManager.h"
class EntityManager
{
public:

	EntityManager(SystemManager* manager);
	~EntityManager() = default;
	Entity* createEntity();
	Entity* createEntityFromCopy(Entity* entity);
	Entity* getEntityByID(EntityID ID);

	void addEntity(Entity* entity);
	void removeEntity(EntityID ID);
	void clean();

	inline unsigned int getEntitiesCount() { return entityCount;  }
	inline SystemManager* getSystemManager() { return systemManager; }
private:

	int entityCount = 0;
	std::unordered_map <EntityID, Entity*> entitiesMap;
	std::vector<Entity*> listOfEntites;


	SystemManager* systemManager;
};

