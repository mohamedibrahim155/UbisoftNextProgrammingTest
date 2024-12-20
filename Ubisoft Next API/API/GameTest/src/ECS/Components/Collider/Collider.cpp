#include "stdafx.h"
#include "Collider.h"
#include "../src/ECS/Entity.h"

Collider::Collider(eShape type, Transform* transform) : IComponent(ComponentType::COLLIDER_COMPONENT)
{
	this->shape = type;
	this->transform = transform;
	center.x = APP_VIRTUAL_WIDTH * 0.5f;
	center.y = APP_VIRTUAL_HEIGHT * 0.5f;
}

