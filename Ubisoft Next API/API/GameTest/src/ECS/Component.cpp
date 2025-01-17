#include "stdafx.h"
#include "Component.h"
#include "Entity.h"

IComponent::IComponent(eComponentType type)
{
	componentID = (int)type;
	gameObject = nullptr;
	m_isEnabled = true;
}

eComponentType IComponent::getComponentType()
{
	return static_cast<eComponentType>(componentID);
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
