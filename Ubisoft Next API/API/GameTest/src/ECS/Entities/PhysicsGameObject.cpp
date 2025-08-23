#include "stdafx.h"
#include "PhysicsGameObject.h"



PhysicsGameObject::PhysicsGameObject(EntityID ID, const eShape& shape, const eBodyType& bodyType) : Entity(ID)
{
	initialize(shape, bodyType);

	addComponent(collider);
	addComponent(rigidbody);
}

PhysicsGameObject::~PhysicsGameObject()
{
}

BoxCollider* PhysicsGameObject::getAsBox()
{
	return (BoxCollider*)collider;
}

CircleCollider* PhysicsGameObject::getAsCircle()
{
	return (CircleCollider*)collider;
}


void PhysicsGameObject::initialize(const eShape& shape, const eBodyType& bodyType)
{
	collider = nullptr;
	switch (shape)
	{
	case eShape::BOX:
		collider = new BoxCollider();
		break;
	case eShape::CIRCLE:
		collider = new CircleCollider();
		break;
	case eShape::LINE:
		collider = new LineCollider();
		break;
	}


	rigidbody = new RigidBody(bodyType);


	
}
