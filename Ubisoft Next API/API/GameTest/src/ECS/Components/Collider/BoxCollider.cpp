#include "stdafx.h"
#include "BoxCollider.h"
#include "../src/Utils/Utils.h"
BoxCollider::BoxCollider() : Collider(eShape::BOX)
{
	m_box.minimum = { -1, -1 };
	m_box.maximum = { 1, 1 };
	m_height = 1;
	m_width = 1;
}

BoxCollider::BoxCollider(SpriteRenderer* spriteRenderer)
	: Collider(eShape::BOX)
{

	this->spriteRenderer = spriteRenderer;
	m_box.minimum = { -1, -1 };
	m_box.maximum = { 1, 1 };

	calculateShape();
}



SBox BoxCollider::getBounds()
{
	return getBox();
}

void BoxCollider::calculateShape()
{


	if (spriteRenderer)
	{
		m_width = spriteRenderer->getSprite()->GetWidth();
		m_height = spriteRenderer->getSprite()->GetHeight();
	}

	float extendX = m_width * 0.5f;
	float extendY = m_height * 0.5f;

	m_box.minimum = { -extendX, -extendY };
	m_box.maximum = { extendX, extendY };

}

SBox BoxCollider::getBox()
{
	SBox box = this->m_box;

	box.minimum.x *= m_scale.x;
	box.minimum.y *= m_scale.y;

	box.maximum.x *= m_scale.x;
	box.maximum.y *= m_scale.y;

	if (transform)
	{
		box.minimum.x *= transform->scale.x;
		box.minimum.y *= transform->scale.y;
		
		box.maximum.x *= transform->scale.x;
		box.maximum.y *= transform->scale.y;
		
		
		box.minimum.x += transform->position.x  + m_center.x;
		box.minimum.y += transform->position.y  + m_center.y;
		
		box.maximum.x += transform->position.x + m_center.x;
		box.maximum.y += transform->position.y + m_center.y;
	}

	box.minimum = box.minimum + m_offset;
	box.maximum = box.maximum + m_offset;


	return box;
}

void BoxCollider::setSize(float x, float y)
{
   m_scale.x = x;
   m_scale.y = y;
}

BoxCollider* BoxCollider::clone() const
{
	return new BoxCollider();
}




void BoxCollider::render(bool isDebugRender)
{
	SBox box = getBox();

	if (!isDebugRender) return;

	Debug::DrawBox(box.minimum, box.maximum, m_debugColor);
}
