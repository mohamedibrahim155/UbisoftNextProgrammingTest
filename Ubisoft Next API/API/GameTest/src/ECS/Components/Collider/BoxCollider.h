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

    SBox getBounds() override;
    void calculateShape() override;

    SBox getBox();



protected:
    
    float width;
    float height;

    SBox mBox;
    
   

   

};

