#pragma once
#include "../../Component.h"
class ScriptComponentBase :  public IComponent
{
public:
	ScriptComponentBase() : IComponent(ComponentType::SCRIPT_COMPONENT){};
	virtual ~ScriptComponentBase() {};

	// Inherited via IComponent
	virtual void start() {};
	virtual void updateComponent() {};
	virtual void render() {};

	// Inherited via IComponent
	virtual ScriptComponentBase* clone() const override
	{
		return new ScriptComponentBase();
	};
};

