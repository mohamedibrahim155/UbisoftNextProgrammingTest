#include "stdafx.h"
#include "Component.h"
#include "Entity.h"

IComponent::IComponent(ComponentType type)
{
	componentID = (int)type;
	gameObject = nullptr;
	isComponentEnabled = true;
}

ComponentType IComponent::GetComponentType()
{
	return static_cast<ComponentType>(componentID);
}

Entity* IComponent::GetEntity() const
{
	return gameObject;
}

void IComponent::SetEntity(Entity* entity)
{
	gameObject = entity;
}

void IComponent::SetEnabled(bool state)
{
	isComponentEnabled = state;
}
