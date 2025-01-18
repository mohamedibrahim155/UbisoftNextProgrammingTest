#include "stdafx.h"
#include "RigidBody.h"
///////////////////////////////////////////////////////////////////////////////
//  Filename: RigidBody.cpp
//  Defines the body type of the component
//  All the physics happens in PhysicsSystem.cpp
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//Default constructor
RigidBody::RigidBody(const eBodyType& type) : 
	IComponent(eComponentType::PHYSICS_COMPONENT)
{
	this->m_bodyType = type;
}

//Duplicate's Constructor
RigidBody::RigidBody(const RigidBody& other) : IComponent(eComponentType::PHYSICS_COMPONENT)
{
	this->m_bodyType = other.m_bodyType;
}

//Duplicate of this component
RigidBody* RigidBody::clone() const
{
	return new RigidBody(*this);
}


