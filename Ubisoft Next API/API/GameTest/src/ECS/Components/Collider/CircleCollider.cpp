#include "stdafx.h"
#include "CircleCollider.h"
#include "../src/ECS/Entity.h"


CircleCollider::CircleCollider(float radius , Transform* transform)
    : Collider(eShape::CIRCLE, transform)
{
    this->radius = radius;

    CalculateShape();
}

CircleCollider::CircleCollider(float width, float height, float radius, Transform* transform)
    : Collider(eShape::CIRCLE, transform)
{
    this->radius = radius;
    this->width = width;
    this->height = height;

    CalculateShape();
}





SCircle CircleCollider::GetCircle()
{
    SCircle circle = m_Circle;


    if (transform)
    {
        circle.centre.x += transform->position.x;
        circle.centre.y += transform->position.y;
        circle.radius *= transform->scale.x;
    }

    return circle;
}

SBox CircleCollider::GetBounds()
{
    SBox box;

    if (transform)
    {
        box.minimum = { transform->position.x - radius, transform->position.y - radius };
        box.maximum = { transform->position.x + radius, transform->position.y + radius };

        box.minimum.x *= transform->scale.x;
        box.minimum.y *= transform->scale.y;

        box.maximum.x *= transform->scale.x;
        box.maximum.y *= transform->scale.y;
    }
    box.minimum = box.minimum + center + offset;
    box.maximum = box.maximum + center + offset;

    return box;
}

void CircleCollider::CalculateShape()
{

   
    if (transform !=  nullptr)
    {
        this->m_Circle.centre  = Vector2(transform->position.x + center.x, transform->position.y + center.y);
    }
    float h = this->height;
    float w = this->width;

    float radius = h;


    radius = (w > h ? w * 0.5f : radius * 0.5f);

    

    this->m_Circle.radius = radius;

}

void CircleCollider::DrawCircle(float cx, float cy, float radius, int segments, const Vector3& color)
{
    const float increment = 2.0f * PI / segments;
    float theta = 0.0f;

    for (int i = 0; i < segments; ++i) 
    {
        // Calculate start and end points of the segment
        float x1 = cx + radius * cosf(theta);
        float y1 = cy + radius * sinf(theta);

        theta += increment;

        float x2 = cx + radius * cosf(theta);
        float y2 = cy + radius * sinf(theta);

        // Draw the line segment
        App::DrawLine(x1, y1, x2, y2, color.x, color.y, color.z);
    }

  

}

void CircleCollider::Render()
{
    SCircle circle = GetCircle();

     const Vector3 color = Vector3(0, 1, 0);

     DrawCircle(circle.centre.x, circle.centre.y, circle.radius, 36, color);

}
