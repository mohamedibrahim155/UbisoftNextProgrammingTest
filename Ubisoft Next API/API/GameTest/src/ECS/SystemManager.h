#pragma once
#include <unordered_map>
#include "System.h"
class SystemManager
{

public:

	void registerSystem(ISystem* system);
	void removeSystem(ISystem* system);

	void addEntity(Entity* entity);
	void removeEntity(EntityID ID);

	void start();
	void updateSystems(float deltaTime);
	void render();
	void cleanSystem();

	ISystem* getSystem(eSystemType type);
	std::vector<Entity*> getEntities() const;
private:

	std::unordered_map<eSystemType, ISystem*> systemsMap;

	std::unordered_map<EntityID,Entity*> entitiesMap;
	std::vector<Entity*> listOfEntities;

};

