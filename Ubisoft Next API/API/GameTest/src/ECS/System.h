#pragma once
#include "Entity.h"
class SystemManager;
class ISystem   
{
public:

	ISystem(std::string  name) : name(name) {};

	virtual ~ISystem() = default;
	virtual void Start()=0;
	virtual void Update(std::vector<Entity*> entities,float deltaTime) = 0;
	virtual void Render(std::vector<Entity*> entities) =0;
	virtual void Cleanups() =0;

	SystemManager* systemManager;
	std::string name;

};

