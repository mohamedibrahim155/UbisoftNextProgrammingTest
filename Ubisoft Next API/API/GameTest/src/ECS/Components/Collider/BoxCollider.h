#pragma once
#include "Collider.h"
class BoxCollider :
    public Collider
{
public:
    BoxCollider(float width, float height, Transform* transform);

    ~BoxCollider() = default;

    // Inherited via Collider
    virtual void Start() {};
    virtual void UpdateComponent() {};
    virtual void Render();

    SBox GetBounds() override;
    void CalculateShape() override;

    SBox GetBox();

protected:
    
    float width;
    float height;

    SBox mBox;
    
   
};

