#pragma once
#include "../Entity.h"
#include "../Components/Collider/BoxCollider.h"
#include "../Components/Collider/CircleCollider.h"
#include "../Components/Collider/LineCollider.h"
#include "../Components/Rigidbody/RigidBody.h"

class PhysicsGameObject : public Entity
{
public:

	PhysicsGameObject(EntityID ID, const eShape& shape, const eBodyType& bodyType);

	~PhysicsGameObject() override;

	BoxCollider* getAsBox();
	CircleCollider* getAsCircle();

	Collider* collider;
	RigidBody* rigidbody;
private:
	void initialize(const eShape& shape, const eBodyType& bodyType);

};

