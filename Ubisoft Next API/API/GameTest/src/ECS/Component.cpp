#include "stdafx.h"
#include "Component.h"
#include "Entity.h"

IComponent::IComponent(ComponentType type)
{
	componentID = (int)type;
	gameObject = nullptr;
	m_isEnabled = true;
}

ComponentType IComponent::getComponentType()
{
	return static_cast<ComponentType>(componentID);
}

Entity* IComponent::getEntity() const
{
	return gameObject;
}

void IComponent::setEntity(Entity* entity)
{
	gameObject = entity;
}

void IComponent::setEnabled(bool state)
{
	m_isEnabled = state;
}

void IComponent::setUI(bool isUI)
{
	this->m_isUI = isUI;
}
