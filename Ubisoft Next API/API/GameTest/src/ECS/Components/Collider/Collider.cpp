#include "stdafx.h"
#include "Collider.h"
#include "../src/ECS/Entity.h"

Collider::Collider(eShape type) : IComponent(ComponentType::COLLIDER_COMPONENT)
{
	this->m_shape = type;
	transform = nullptr;
	spriteRenderer = nullptr;

	m_center.x = APP_VIRTUAL_WIDTH * 0.5f;
	m_center.y = APP_VIRTUAL_HEIGHT * 0.5f;
}

void Collider::Init()
{
	transform = &gameObject->transform;

	if (!spriteRenderer)
	{
		spriteRenderer = gameObject->m_sprite;
	}
	calculateShape();
}



void Collider::SetTrigger(bool trigger)
{
	m_isTrigger = trigger;
}



