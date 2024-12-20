#pragma once
#include "Collider.h"
class CircleCollider :
    public Collider
{
public:
    CircleCollider(float radius, Transform* transform);
    CircleCollider(float width, float height,float radius, Transform* transform);
    ~CircleCollider() override {};

     void Start() override {};
     void UpdateComponent() override {};
     void Render()  override;
     void SetRadius(float radius) { this->radius = radius; };

     float GetRadius() const { return radius; };

     SCircle GetCircle();
protected:

    float radius;
    float width;
    float height;

    SCircle m_Circle;

    // Inherited via Collider
    SBox GetBounds() override;
    void CalculateShape() override;

    
    void DrawCircle(float cx, float cy, float radius, int segments, const Vector3& color);
};

