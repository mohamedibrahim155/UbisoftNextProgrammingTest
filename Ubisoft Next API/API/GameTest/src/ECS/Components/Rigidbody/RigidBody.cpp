#include "stdafx.h"
#include "RigidBody.h"

RigidBody::RigidBody(const eBodyType& type) : 
	IComponent(eComponentType::PHYSICS_COMPONENT)
{
	this->bodyType = type;
}

RigidBody::RigidBody(const RigidBody& other) : IComponent(eComponentType::PHYSICS_COMPONENT)
{
	this->bodyType = other.bodyType;
}

RigidBody* RigidBody::clone() const
{
	return new RigidBody(*this);
}


