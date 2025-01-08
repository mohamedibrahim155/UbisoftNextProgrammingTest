#include "stdafx.h"
#include "CircleCollider.h"
#include "../src/Utils/Utils.h"
CircleCollider::CircleCollider() : Collider(eShape::CIRCLE)
{
    m_circle.centre = { m_center.x, m_center.y };
    m_circle.radius = 1;
    m_width = 1;
    m_height = 1;
}

CircleCollider::CircleCollider(float radius) : Collider(eShape::CIRCLE)
{
    m_circle.centre = { m_center.x, m_center.y };
    m_circle.radius = radius;

}

CircleCollider::CircleCollider(const CircleCollider& other) : Collider(eShape::CIRCLE)
{
    this->m_circle = other.m_circle;
}






SCircle CircleCollider::getCircle()
{
    SCircle circle = m_circle;

    circle.radius *= MathF::Max(m_scale.x, m_scale.y);

    if (transform)
    {
        circle.centre.x += transform->position.x;
        circle.centre.y += transform->position.y;
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
        box.minimum = { transform->position.x - m_circle.radius, transform->position.y - m_circle.radius };
        box.maximum = { transform->position.x + m_circle.radius, transform->position.y + m_circle.radius };

        box.minimum.x *= transform->scale.x;
        box.minimum.y *= transform->scale.y;

        box.maximum.x *= transform->scale.x;
        box.maximum.y *= transform->scale.y;
    }
    box.minimum = box.minimum + m_center + m_offset;
    box.maximum = box.maximum + m_center + m_offset;

    return box;
}

void CircleCollider::calculateShape()
{
    if (spriteRenderer)
    {
        m_width = spriteRenderer->getSprite()->GetWidth();
        m_height = spriteRenderer->getSprite()->GetHeight();
    }

    if (transform)
    {
        m_circle.centre = Vector2(m_center.x,m_center.y);
    }

    float h = m_height;
    float w = m_width;

    float radius = h;

    radius = (w > h ? w * 0.5f : radius * 0.5f);

    this->m_circle.radius = radius;

}



CircleCollider* CircleCollider::clone() const
{
    return new CircleCollider(*this);
}


void CircleCollider::render()
{
    SCircle circle = getCircle();

     Debug::DrawCircle(circle.centre.x, circle.centre.y, circle.radius, 36, m_debugColor);

}
