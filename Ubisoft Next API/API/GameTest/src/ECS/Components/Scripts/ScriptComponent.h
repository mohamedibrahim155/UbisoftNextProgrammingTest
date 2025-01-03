#pragma once
#include "../../Component.h"
class BaseScriptComponent :  public IComponent
{
public:
	BaseScriptComponent() : IComponent(ComponentType::SCRIPT_COMPONENT){};
	virtual ~BaseScriptComponent() {};

	// Inherited via IComponent
	virtual void start() {};
	virtual void updateComponent() {};
	virtual void render() {};

	// Inherited via IComponent
	virtual BaseScriptComponent* clone() const override
	{
		return new BaseScriptComponent();
	};
};

