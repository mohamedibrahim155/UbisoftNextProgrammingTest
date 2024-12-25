#include "stdafx.h"
#include "Transform.h"

Transform::Transform() : IComponent(ComponentType::TRANSFORM_COMPONENT)
{
	this->position = Vector3::Zero();
	this->scale = Vector2::One();
}
 
Transform::Transform(const Transform& other) : IComponent(ComponentType::TRANSFORM_COMPONENT)
{
	this->position = other.position;
	this->scale = other.scale;
}

Transform::Transform(Vector3 position, Vector2 scale) :  IComponent(ComponentType::TRANSFORM_COMPONENT)
{
	this->position = position;
	this->scale = scale;
}

Transform::Transform(Vector2 position, Vector2 scale) : IComponent(ComponentType::TRANSFORM_COMPONENT)
{
	this->position =  Vector3(position.x, position.y, 0);
	this->scale = scale;
}

Transform* Transform::Clone() const
{
	return new Transform(*this);
}
