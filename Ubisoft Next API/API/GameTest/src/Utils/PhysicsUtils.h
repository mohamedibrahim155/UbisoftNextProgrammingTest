#pragma once
#include "../src/ECS/Components/Rigidbody/RigidBody.h"
#include "../src/ECS/Entity.h"
#include"../src/ECS/Components/Collider/Collider.h"

class Physics
{
public:
	static  bool CheckCollision(Collider* A, Collider* B);
	static  bool CircleVSCirce(SCircle* circleA, SCircle* circleB);
	static  bool BoxVsBox(SBox* boxA, SBox* boxB);
	static void ResolveCollision(RigidBody* bodyA, RigidBody* bodyB, Transform* a, Transform* b);

};

