#pragma once
#include "Collider.h"
class BoxCollider :
    public Collider
{
public:
    BoxCollider();

    ~BoxCollider() = default;

    // Inherited via Collider
    virtual void Start() {};
    virtual void UpdateComponent() {};
    virtual void Render();
    BoxCollider* Clone() const override;

    SBox GetBounds() override;
    void CalculateShape() override;

    SBox GetBox();



protected:
    
    float width;
    float height;

    SBox mBox;
    
   

   

};

