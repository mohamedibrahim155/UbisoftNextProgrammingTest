#include "stdafx.h"
#include "Transform.h"

Transform::Transform() : IComponent(eComponentType::TRANSFORM_COMPONENT)
{
	this->position = Vector3::Zero();
	this->scale = Vector2::One();
}
 
Transform::Transform(const Transform& other) : IComponent(eComponentType::TRANSFORM_COMPONENT)
{
	this->position = other.position;
	this->scale = other.scale;
}

Transform::Transform(Vector3 position, Vector2 scale) :  IComponent(eComponentType::TRANSFORM_COMPONENT)
{
	this->position = position;
	this->scale = scale;
}

Transform::Transform(Vector2 position, Vector2 scale) : IComponent(eComponentType::TRANSFORM_COMPONENT)
{
	this->position =  Vector3(position.x, position.y, 0);
	this->scale = scale;
}

Transform* Transform::clone() const
{
	return new Transform(*this);
}
