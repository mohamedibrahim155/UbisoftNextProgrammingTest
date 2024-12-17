#include "stdafx.h"
#include "Component.h"
#include "Entity.h"

IComponent::IComponent(ComponentType type)
{
	componentID = (int)type;
	entityRef = nullptr;
	isComponentEnabled = true;
}

ComponentType IComponent::GetComponentType()
{
	return static_cast<ComponentType>(componentID);
}

void IComponent::SetEntity(Entity* entity)
{
	entityRef = entity;
}

void IComponent::SetEnabled(bool state)
{
	isComponentEnabled = true;
}
