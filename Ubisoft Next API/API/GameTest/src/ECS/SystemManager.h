#pragma once
#include <unordered_map>
#include "System.h"
class SystemManager
{

public:

	void RegisterSystem(ISystem* system);
	void RemoveSystem(ISystem* system);

	void AddEntity(Entity* entity);
	void RemoveEntity(EntityID ID);

	void Start();
	void UpdateSystems(float deltaTime);
	void Render();
	void CleanSystem();

	ISystem* GetSystem(eSystemType type);
	std::vector<Entity*> GetEntities() const;
private:

	std::unordered_map<eSystemType, ISystem*> systemsMap;

	std::unordered_map<EntityID,Entity*> entitiesMap;
	std::vector<Entity*> listOfEntities;

};

