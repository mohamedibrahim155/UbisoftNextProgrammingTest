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
    Transform* Clone() const override;

    Vector3 position;
    Vector2 scale;

    Vector3 GetPosition() const { return position; }
    void SetPosition(const Vector3& pos) { position = pos; }
private:
    void Start() override {} ;
    void UpdateComponent() override {};
    void Render() override {};


  

};

