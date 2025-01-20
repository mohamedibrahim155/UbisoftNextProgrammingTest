#include "stdafx.h"
#include "Collider.h"
#include "../src/ECS/Entity.h"

Collider::Collider(eShape type) : IComponent(eComponentType::COLLIDER_COMPONENT)
{
	this->m_shape = type;
	transform = nullptr;
	spriteRenderer = nullptr;

	m_screenCenter.x = APP_VIRTUAL_WIDTH * 0.5f;
	m_screenCenter.y = APP_VIRTUAL_HEIGHT * 0.5f;
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

void Collider::cleanUp()
{
	OnCollision.clear();
	OnCollisionEnter.clear();
	OnCollisionExit.clear();
	OnTrigger.clear();
	OnTriggerEnter.clear();
	OnTriggerExit.clear();
}


void Collider::SetTrigger(bool trigger)
{
	m_isTrigger = trigger;
}



