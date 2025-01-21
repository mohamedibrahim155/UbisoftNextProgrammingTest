///////////////////////////////////////////////////////////////////////////////
// Filename: SystemManager.h
// System Manager holds and Update every entites in the world
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <unordered_map>
#include "System.h"
#include "../Events/Event.h"
class SystemManager
{

public:

	// adds system in a map
	void registerSystem(ISystem* system);

	// removes  system in a map
	void removeSystem(ISystem* system);

	//adds a entity to the system
	void addEntityToSystem(Entity* entity);
	void removeEntity(EntityID ID);

	//Inits entities
	void start();

	// updates entities everyframe
	void updateSystems(float deltaTime);

	// render entities everyframe
	void render();

	//cleans the data of entites, attached component and System while shutdown
	void cleanups();

	//clear the maps of system
	void cleanSystem();

	// sets the debug view of colliders
	void setDebugVisible(bool isVisible);

	//getters
	bool IsDebug() const;
	int getEntitiesCount() const;

	Entity* getEntityByID(EntityID ID);
	std::vector<Entity*> getEntities() const;
	ISystem* getSystem(eSystemType type);

	//Events when an entity added to system
	CEvent<Entity*> OnEntityAdded;

	//Events when an entity removed from system
	CEvent<Entity*> OnEntityRemoved;


private:

	//holds maps of different system
	std::unordered_map<eSystemType, ISystem*> m_systemsMap;

	//Hold the enities in the entire world
	std::unordered_map<EntityID,Entity*> m_entitiesMap;
	std::vector<Entity*> m_listOfEntities;

	//cleans entites
	void clearEntities();

	//Cleans the systems entities
	//"canDelete" flag to not delete the register system while scene transition

	void clearSystems(bool canDelete = true);

	bool m_debugVisible = false;
};

