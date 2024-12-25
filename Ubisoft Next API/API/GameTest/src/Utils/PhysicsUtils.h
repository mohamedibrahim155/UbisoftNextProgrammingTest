#pragma once
#include "../src/ECS/Components/Rigidbody/RigidBody.h"
#include "../src/ECS/Entity.h"
#include"../src/ECS/Components/Collider/Collider.h"
#include "../src/Utils/Utils.h"
class Physics
{
public:
	static  bool CheckCollision(Collider* A, Collider* B);
	static  bool CircleVsCircle(SCircle* circleA, SCircle* circleB);
	static  bool BoxVsBox(SBox* boxA, SBox* boxB);
	static void ResolveCollision(RigidBody* bodyA, RigidBody* bodyB, Transform* a, Transform* b);
	static bool LineVsLine(SLine* lineA, SLine* lineB);
	static bool LineVsCircle(SLine* line, SCircle* circle);
	static bool LineVsBox(SLine* line, SBox* box);
	static bool CircleVsBox(SCircle* circle, SBox* box);
	static bool Raycast(Collider* colliderToCheck ,Vector2 startpoint, Vector2 direction, float distance);

};

