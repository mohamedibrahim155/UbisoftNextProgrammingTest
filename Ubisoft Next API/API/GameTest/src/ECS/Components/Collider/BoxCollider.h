#pragma once
#include "Collider.h"
class BoxCollider :
    public Collider
{
public:
    BoxCollider();
    BoxCollider(SpriteRenderer* spriteRenderer);

    ~BoxCollider() = default;

    // Inherited via Collider
    virtual void start() {};
    virtual void updateComponent() {};
    virtual void render();
    BoxCollider* clone() const override;

    SBox GetBounds() override;
    void CalculateShape() override;

    SBox GetBox();



protected:
    
    float width;
    float height;

    SBox mBox;
    
   

   

};

