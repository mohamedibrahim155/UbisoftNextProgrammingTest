#include "stdafx.h"
#include "Transform.h"

Transform::Transform() : IComponent(ComponentType::TRANSFORM_COMPONENT)
{
	this->position = Vector3::Zero();
	this->scale = Vector3::One();
}

Transform::Transform(Vector3 position, Vector3 scale) :  IComponent(ComponentType::TRANSFORM_COMPONENT)
{
	this->position = position;
	this->scale = scale;
}

Transform::Transform(Vector2 position, Vector2 scale) : IComponent(ComponentType::TRANSFORM_COMPONENT)
{
	this->position =  Vector3(position.x, position.y, 0);
	this->scale =  Vector3(scale.x, scale.y, 0);
}
