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
     void setRadius(float radius) { m_circle.radius = radius; };

     float getRadius() const { return m_circle.radius; };

     SCircle getCircle();
protected:

    float m_width;
    float m_height;

    SCircle m_circle;

    // Inherited via Collider
    SBox getBounds() override;
    void calculateShape() override;

 
};

