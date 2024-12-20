#pragma once
#include "../../Component.h"

enum class eBodyType
{
    STATIC,
    DYNAMIC,
};
class RigidBody :
    public IComponent
{
public:
    RigidBody(const eBodyType& type);
    ~RigidBody() override =default;


    // Inherited via IComponent
    void Start() override {};
    void UpdateComponent() override {};
    void Render() override {};


    void SetBodyType(const eBodyType& type) { this->bodyType = type; };
    void SetGravity(const float& gravity) { this->gravityScale = gravity; };
    void SetMass(const float& mass) { this->mass = mass; };
    eBodyType GetbodyType() const { return bodyType; };
    float GetGravityScale() const { return  gravityScale; };
    float GetMass() const { return  mass; };


    Vector2 velocity;
protected:
    eBodyType bodyType = eBodyType::STATIC;
    float mass = 1;
    float gravityScale = 1;

};

