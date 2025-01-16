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

	void addEntity(Entity* entity);
	void removeEntity(EntityID ID);
	void clean();

private:

	int m_entityID = 0;

	std::vector<Entity*> m_listOfEntites;
	SystemManager* m_systemManager;

	void destroyEntity(Entity* entity);
	void subscribeOnDestroy(Entity* entity);

};

