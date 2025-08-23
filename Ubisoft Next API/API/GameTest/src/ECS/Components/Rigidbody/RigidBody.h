///////////////////////////////////////////////////////////////////////////////
// Filename: Rigidbody.h
// RigidBody determines the physics component of an Entity
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#pragma once
#include "../../Component.h"

enum class eBodyType
{
    STATIC,
    DYNAMIC,
};

//-----------------------------------------------------------------------------
// RigidBody inherited from base Component
//-----------------------------------------------------------------------------
class RigidBody :
    public IComponent
{
public:
    RigidBody(const eBodyType& type);
    RigidBody(const RigidBody& other);
    ~RigidBody() override =default;


    // Inherited via IComponent
    void start() override {};
    void updateComponent() override {};
    void render(bool isDebugVisible) override {};
    void cleanUp() override {};
    RigidBody* clone() const override;

    //Setters
    void setBodyType(const eBodyType& type) { this->m_bodyType = type; };
    void setGravity(const float& gravity) { this->m_gravityScale = gravity; };
    void setMass(const float& mass) { this->m_mass = mass; };
    void setDrag(const float& drag) { this->m_drag = drag; };

    //Getters
    float getGravityScale() const { return  m_gravityScale; };
    float getMass() const { return  m_mass; };
    float getInverseMass() const { return 1 / m_mass; };
    float getDrag() const { return  m_drag; };
    eBodyType getbodyType() const { return m_bodyType; };
 

    Vector2 velocity{ 0.0f, 0.0f };
    Vector2 force{ 0.0,0.0 };
    float bounciness = 0;

protected:
    eBodyType m_bodyType = eBodyType::STATIC;
    float m_mass = 10;
    float m_gravityScale = 1;
    float m_drag = 0.5;
};

