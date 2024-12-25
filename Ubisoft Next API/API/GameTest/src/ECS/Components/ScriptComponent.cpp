#include "stdafx.h"
#include "ScriptComponent.h"


ScriptComponent::ScriptComponent() : IComponent(ComponentType::SCRIPT_COMPONENT)
{
}


ScriptComponent* ScriptComponent::Clone() const
{
	return new ScriptComponent();
}


