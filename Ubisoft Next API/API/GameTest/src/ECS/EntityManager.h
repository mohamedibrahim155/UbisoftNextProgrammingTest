
///////////////////////////////////////////////////////////////////////////////
// Filename: EntityManager.h
// Entity manager resposnible for creating Enities and giving ID's
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Entity.h"
#include <unordered_map>
#include "SystemManager.h"

//------------------------------------------------------------------------------
// Entity manager responsible for creating Enities and giving ID's
//--------------------------------------------------------------------------
class EntityManager
{
public:

	EntityManager(SystemManager* manager);
	~EntityManager() = default;

	//creates entites with Unique ID's
	Entity* createEntity();

	//creates a copy of entity
	Entity* createEntityFromCopy(Entity* entity);

	// add entity to the system manager
	void addEntity(Entity* entity);

	// removed the entity from the system manager
	void removeEntity(EntityID ID);
	void clean();

private:

	int m_entityID = 0;
	SystemManager* m_systemManager;

	//destroy dynamic entity in runtime
	void destroyEntity(Entity* entity);

	//event to destroy
	void subscribeOnDestroy(Entity* entity);

};

