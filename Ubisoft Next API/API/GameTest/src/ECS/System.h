#pragma once
#include "Entity.h"
class SystemManager;
class ISystem   
{
public:

	ISystem(std::string  name) : name(name) {};

	virtual ~ISystem() = default;
	virtual void Start(std::vector<Entity*> entities)=0;
	virtual void Update(std::vector<Entity*> entities,float deltaTime) = 0;
	virtual void Render(std::vector<Entity*> entities) =0;
	virtual void Cleanups() =0;
	virtual void RemoveEntity(Entity* entity);
	virtual void AddEntity(Entity* entity, IComponent* component);

	SystemManager* systemManager;
	std::string name;
	std::unordered_map<Entity*, IComponent*> listOfRenderers;

};

