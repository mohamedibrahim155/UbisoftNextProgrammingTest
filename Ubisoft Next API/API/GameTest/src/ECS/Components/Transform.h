#pragma once
#include "../Component.h"
#include "../src/Vector.h"

class Transform :public IComponent
    
{
public:

    Transform();
    Transform(const Transform& other);
    Transform(Vector3 position, Vector2 scale);
    Transform(Vector2 position, Vector2 scale);

    // Inherited via IComponent
    Transform* clone() const override;

    // Transform Data
    Vector3 position;
    float rotation;
    Vector2 scale;

private:
    void start() override {} ;
    void updateComponent() override {};
    void render() override {};
    void cleanUp() override {};

  

};

