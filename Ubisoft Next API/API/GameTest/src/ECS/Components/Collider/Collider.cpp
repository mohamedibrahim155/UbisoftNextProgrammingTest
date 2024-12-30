#include "stdafx.h"
#include "Collider.h"
#include "../src/ECS/Entity.h"

Collider::Collider(eShape type) : IComponent(ComponentType::COLLIDER_COMPONENT)
{
	this->shape = type;
	transform = nullptr;
	spriteRenderer = nullptr;

	center.x = APP_VIRTUAL_WIDTH * 0.5f;
	center.y = APP_VIRTUAL_HEIGHT * 0.5f;
}

void Collider::Init()
{
	transform = &gameObject->transform;

	if (!spriteRenderer)
	{
		spriteRenderer = gameObject->m_sprite;
	}
	CalculateShape();
}



void Collider::SetTrigger(bool trigger)
{
	isTrigger = trigger;
}



