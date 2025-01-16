#include "stdafx.h"
#include "CircleCollider.h"
#include "../src/Utils/Utils.h"
CircleCollider::CircleCollider() : Collider(eShape::CIRCLE)
{
    m_circle.centre = { m_screenCenter.x, m_screenCenter.y };
    m_circle.radius = 1;
    m_width = 1;
    m_height = 1;
}

CircleCollider::CircleCollider(float radius) : Collider(eShape::CIRCLE)
{
    m_circle.centre = { m_screenCenter.x, m_screenCenter.y };
    m_circle.radius = radius;

}

CircleCollider::CircleCollider(const CircleCollider& other) : Collider(eShape::CIRCLE)
{
    this->m_circle = other.m_circle;
	this->m_width = other.m_width;
	this->m_height = other.m_height;
}






SCircle CircleCollider::getCircle()
{
    SCircle circle = m_circle;

    circle.radius *= MathF::Max(m_scale.x, m_scale.y);

    if (transform)
    {
        circle.centre.x += transform->localPosition.x;
        circle.centre.y += transform->localPosition.y;
        circle.radius   *= transform->scale.x;
    }

    circle.centre = circle.centre + m_offset;

    return circle;
}

SBox CircleCollider::getBounds()
{
    SBox box;

    if (transform)
    {
        box.minimum = { transform->localPosition.x - m_circle.radius, transform->localPosition.y - m_circle.radius };
        box.maximum = { transform->localPosition.x + m_circle.radius, transform->localPosition.y + m_circle.radius };

        box.minimum.x *= transform->scale.x;
        box.minimum.y *= transform->scale.y;

        box.maximum.x *= transform->scale.x;
        box.maximum.y *= transform->scale.y;
    }
    box.minimum = box.minimum  + m_offset;
    box.maximum = box.maximum  + m_offset;

    return box;
}

void CircleCollider::calculateShape()
{
    if (spriteRenderer)
    {
        m_width = spriteRenderer->getSprite()->GetWidth();
        m_height = spriteRenderer->getSprite()->GetHeight();
    }

    m_circle.centre = Vector2(m_screenCenter.x, m_screenCenter.y);

    float h = m_height;
    float w = m_width;

    float localRadius = h;

    localRadius = (w > h ? w * 0.5f : localRadius * 0.5f);

    m_circle.radius = localRadius;

}



CircleCollider* CircleCollider::clone() const
{
    return new CircleCollider(*this);
}

void CircleCollider::setHeight(const float& height)
{
	m_height = height;
}

void CircleCollider::setWidth(const float& width)
{
	m_width = width;
}



void CircleCollider::render(bool isDebugVisible)
{
    if (!m_isEnabled) return;

    SCircle circle = getCircle();

    if (!isDebugVisible) return;

     Debug::DrawCircle(circle.centre.x, circle.centre.y, circle.radius, 36, m_debugColor);

}
