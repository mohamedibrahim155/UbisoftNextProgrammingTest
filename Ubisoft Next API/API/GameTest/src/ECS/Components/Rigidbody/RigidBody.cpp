#include "stdafx.h"
#include "RigidBody.h"

RigidBody::RigidBody(const eBodyType& type) : 
	IComponent(ComponentType::PHYSICS_COMPONENT)
{
	this->bodyType = type;
}


