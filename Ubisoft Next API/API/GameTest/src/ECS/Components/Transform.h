#pragma once
#include "../Component.h"
#include "../src/Vector.h"

class Transform :public IComponent
    
{
public:

    Transform();
    Transform(Vector3 position, Vector3 scale);
    Transform(Vector2 position, Vector2 scale);

    Vector3 position;
    Vector3 scale;

private:
    void Initialise() override {} ;
    void UpdateComponent() override {};
    void Render() override {};

};

