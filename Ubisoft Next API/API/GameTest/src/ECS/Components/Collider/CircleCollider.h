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
     void setRadius(float radius) { m_Circle.radius = radius; };

     float getRadius() const { return m_Circle.radius; };

     SCircle getCircle();
protected:

    float width;
    float height;

    SCircle m_Circle;

    // Inherited via Collider
    SBox getBounds() override;
    void calculateShape() override;

    
    void DrawCircle(float cx, float cy, float radius, int segments, const Vector3& color);

 
};

