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


	void start();
	void updateSystems(float deltaTime);
	void render();
	void cleanups();
	void cleanSystem();

	void setDebugVisible(bool isVisible);

	bool IsDebug() const;
	int getEntitiesCount() const;

	Entity* getEntityByID(EntityID ID);
	std::vector<Entity*> getEntities() const;
	ISystem* getSystem(eSystemType type);


	CEvent<Entity*> OnEntityAdded;
	CEvent<Entity*> OnEntityRemoved;


private:

	std::unordered_map<eSystemType, ISystem*> m_systemsMap;

	std::unordered_map<EntityID,Entity*> m_entitiesMap;
	std::vector<Entity*> m_listOfEntities;

	void clearEntities();
	void clearSystems(bool canDelete = true);

	bool m_debugVisible = true;
};

