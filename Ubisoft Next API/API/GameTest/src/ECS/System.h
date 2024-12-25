#pragma once
#include "Entity.h"
class SystemManager;

enum class eSystemType
{
	UNKNOWN,
	CUSTOMSCRIPT_SYSTEM,
	MOVEMENT_SYSTEM,
	PHYSICS_SYSTEM,
	RENDER_SYSTEM,
};
class ISystem   
{
public:

	ISystem(std::string  name, eSystemType type) : name(name), systemType(type) {};
	virtual ~ISystem() = default;
	virtual void Start(std::vector<Entity*> entities)=0;
	virtual void Update(std::vector<Entity*> entities,float deltaTime) = 0;
	virtual void Render(std::vector<Entity*> entities) =0;
	virtual void Cleanups() =0;

	SystemManager* systemManager;
	std::string name;
	eSystemType systemType;

};

