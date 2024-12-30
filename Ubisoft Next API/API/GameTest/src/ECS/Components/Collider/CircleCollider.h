#pragma once
#include "Collider.h"
class CircleCollider :
    public Collider
{
public:
    CircleCollider();
    CircleCollider(float radius);
    CircleCollider(const CircleCollider& other);

    ~CircleCollider() override {};

    // Inherited via Collider
    void start() override {};
     void updateComponent() override {};
     void render()  override;
     CircleCollider* clone() const override;
     void SetRadius(float radius) { m_Circle.radius = radius; };

     float GetRadius() const { return m_Circle.radius; };

     SCircle GetCircle();
protected:

    float width;
    float height;

    SCircle m_Circle;

    // Inherited via Collider
    SBox GetBounds() override;
    void CalculateShape() override;

    
    void DrawCircle(float cx, float cy, float radius, int segments, const Vector3& color);

 
};

