#include "stdafx.h"
#include "PhysicsUtils.h"
#include "../src/ECS/Components/Collider/CircleCollider.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
bool Physics::CheckCollision(Collider* colliderA, Collider* colliderB)
{
	if (colliderA->GetShapeType() == eShape::CIRCLE && colliderB->GetShapeType() == eShape::CIRCLE)
	{
		CircleCollider* circleA = (CircleCollider*)colliderA;
		CircleCollider* circleB = (CircleCollider*)colliderB;


		return CircleVSCirce(&circleA->GetCircle(), &circleB->GetCircle());
	}

	if (colliderA->GetShapeType() == eShape::BOX && colliderB->GetShapeType() ==eShape::BOX)
	{
		BoxCollider* boxA = (BoxCollider*)colliderA;
		BoxCollider* boxB = (BoxCollider*)colliderB;

		return BoxVsBox(&boxA->GetBox(), &boxB->GetBox());
	}


	return false;
}

bool Physics::CircleVSCirce(SCircle* circleA, SCircle* circleB)
{
	float radius = circleA->radius + circleB->radius;

	Vector2 diff = circleA->centre - circleB->centre;
	float dot = diff.x * diff.x + diff.y * diff.y;

	//float dot = diff.LengthSquared();

	return dot <= radius * radius;
}

bool Physics::BoxVsBox(SBox* boxA, SBox* boxB)
{
	bool overlapX = boxA->maximum.x >= boxB->minimum.x && boxA->minimum.x <= boxB->maximum.x;
	bool overlapY = boxA->maximum.y >= boxB->minimum.y && boxA->minimum.y <= boxB->maximum.y;

	return overlapX && overlapY;
}

void Physics::ResolveCollision(RigidBody* bodyA, RigidBody* bodyB, Transform* a, Transform* b)
{
	


	bodyA->velocity = { 0,0 };


}
