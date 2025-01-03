#pragma once
#include "../src/ECS/Components/Rigidbody/RigidBody.h"
#include "../src/ECS/Entity.h"
#include"../src/ECS/Components/Collider/Collider.h"
#include "../src/Utils/Utils.h"

struct RaycastHit {
	Collider* collider = nullptr; // The collider that was hit
	Vector2 hitPoint;             // The point of intersection
	float hitDistance = 0.0f;     // The distance to the hit
};
class Physics
{
public:
	static  bool CheckCollision(Collider* A, Collider* B , std::vector<Vector2>& collisionPt, std::vector<Vector2>& collisionNormal);
	static  bool CircleVsCircle(SCircle* circleA, SCircle* circleB, std::vector<Vector2>& collisionPt, std::vector<Vector2>& collisionNormal);
	static  bool BoxVsBox(SBox* boxA, SBox* boxB, std::vector<Vector2>& collisionPt, std::vector<Vector2>& collisionNormal);
	static  bool LineVsLine(SLine* lineA, SLine* lineB, Vector2& intersectionPoint = Vector2::Zero());
	static  bool LineVsCircle(SLine* line, SCircle* circle, Vector2& hitPoint = Vector2::Zero());
	static  bool LineVsBox(SLine* line, SBox* box, Vector2& intersectionPoint = Vector2::Zero());
	static  bool CircleVsBox(SCircle* circle, SBox* box, bool isCircle, std::vector<Vector2>& collisionPt, std::vector<Vector2>& collisionNormal);
	static  bool Raycast(Vector2 startpoint, Vector2 direction, float distance, RaycastHit& hitInfo);

	

private:

	static float SqDistPointAABB(Vector2 point,  SBox* b);
	static const Vector2& ClosestPtAABB(Vector2& point, SBox* b);
	
};

