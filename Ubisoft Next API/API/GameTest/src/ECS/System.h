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
	PARTILCE_SYSTEM,
};
class ISystem   
{
public:

	ISystem(std::string  name, eSystemType type) : m_name(name), m_systemType(type) {};
	virtual ~ISystem() = default;
	virtual void start(std::vector<Entity*> entities)=0;
	virtual void update(std::vector<Entity*> entities,float deltaTime) = 0;
	virtual void render(std::vector<Entity*> entities, bool isDebugVisible) =0;
	virtual void cleanups() =0;

	SystemManager* m_systemManager;
	std::string m_name;
	eSystemType m_systemType;

};

