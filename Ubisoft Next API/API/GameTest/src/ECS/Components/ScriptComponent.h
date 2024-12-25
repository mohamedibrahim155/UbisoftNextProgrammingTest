#pragma once
#include "../Component.h"
class ScriptComponent :  public IComponent
{
public:
	ScriptComponent();
	virtual ~ScriptComponent() {};
	// Inherited via IComponent
	virtual void Start() {};
	virtual void UpdateComponent() {} ;
	virtual void Render() {};

	// Inherited via IComponent
	virtual ScriptComponent* Clone() const override;
};

