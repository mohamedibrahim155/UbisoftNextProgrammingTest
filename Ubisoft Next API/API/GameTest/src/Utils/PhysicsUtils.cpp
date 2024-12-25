#include "stdafx.h"
#include "PhysicsUtils.h"
#include "../src/ECS/Components/Collider/CircleCollider.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/ECS/Components/Collider/LineCollider.h"
bool Physics::CheckCollision(Collider* colliderA, Collider* colliderB)
{

	switch (colliderA->GetShapeType())
	{

#pragma region CircleVS

	
	case eShape::CIRCLE :

		
		switch (colliderB->GetShapeType())
		{
		case eShape::CIRCLE:

			return CircleVsCircle(&dynamic_cast<CircleCollider*>(colliderA)->GetCircle(),
				&dynamic_cast<CircleCollider*>(colliderB)->GetCircle());

		case eShape::BOX:

			return CircleVsBox(&dynamic_cast<CircleCollider*>(colliderA)->GetCircle(),
				&dynamic_cast<BoxCollider*>(colliderB)->GetBox());


		case eShape::LINE:

			return LineVsCircle(&dynamic_cast<LineCollider*>(colliderB)->GetLine(),
				&dynamic_cast<CircleCollider*>(colliderA)->GetCircle());
		}

		break;
     #pragma endregion

#pragma region BoxVS
	case eShape::BOX:

		switch (colliderB->GetShapeType())
		{

		case eShape::CIRCLE:
			return CircleVsBox(&dynamic_cast<CircleCollider*>(colliderB)->GetCircle(),
				&dynamic_cast<BoxCollider*>(colliderA)->GetBox());

		case eShape::BOX:

			return BoxVsBox(&dynamic_cast<BoxCollider*>(colliderA)->GetBox(), 
				&dynamic_cast<BoxCollider*>(colliderB)->GetBox());


		case eShape::LINE:
			return LineVsBox(&dynamic_cast<LineCollider*>(colliderB)->GetLine(),
				&dynamic_cast<BoxCollider*>(colliderA)->GetBox());
		}

		break;

#pragma endregion

#pragma region LineVs

	case eShape::LINE:

		switch (colliderB->GetShapeType())
		{


		case eShape::CIRCLE:


			return LineVsCircle(&dynamic_cast<LineCollider*>(colliderA)->GetLine(), 
				&dynamic_cast<CircleCollider*>(colliderB)->GetCircle());

		case eShape::BOX:

			return LineVsBox(&dynamic_cast<LineCollider*>(colliderA)->GetLine(),
				&dynamic_cast<BoxCollider*>(colliderB)->GetBox());


		case eShape::LINE:

			return LineVsLine(&dynamic_cast<LineCollider*>(colliderA)->GetLine(),
				&dynamic_cast<LineCollider*>(colliderB)->GetLine());
		}

		break;
#pragma endregion

	}
	/*if (colliderA->GetShapeType() == eShape::CIRCLE && colliderB->GetShapeType() == eShape::CIRCLE)
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
	}*/


	return false;
}

bool Physics::CircleVsCircle(SCircle* circleA, SCircle* circleB)
{
	float radius = circleA->radius + circleB->radius;

	Vector2 diff = circleA->centre - circleB->centre;
	float dot = diff.x * diff.x + diff.y * diff.y;

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

bool Physics::LineVsLine(SLine* lineA, SLine* lineB)
{


	Vector2 AB = { lineA->endPoint.x - lineA->startPoint.x, lineA->endPoint.y - lineA->startPoint.y };       // B-A
	Vector2 CD = { lineB->endPoint.x - lineB->startPoint.x, lineB->endPoint.y - lineB->startPoint.y };       // D-C
	Vector2 AC = { lineB->startPoint.x - lineA->startPoint.x,  lineB->startPoint.y - lineA->startPoint.y };  // C-A



	float determinant = Vector2::Cross(AB, CD);

	if (std::abs(determinant) < 1e-6f)
	{
		return false;
	}


	// Calculate parameters t and u
	float t = Vector2::Cross(AC, CD) / determinant;
	float u = Vector2::Cross(AC, AB) / determinant;

	
	// Checks if t and u are within [0, 1]
	return  (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f);

}

bool Physics::LineVsCircle(SLine* line, SCircle* circle)
{

	Vector2 dir = line->endPoint - line->startPoint;

	Vector2 startToCentre = circle->centre - line->startPoint;



	float projection = Vector2::Dot(startToCentre, dir) / Vector2::Dot(dir, dir);
	projection = MathF::Max(0.0f, MathF::Min(1.0f, projection)); // Clamp to [0, 1]

	Vector2 closestPoint = line->startPoint + dir * projection;

	Vector2 circleToClosest = closestPoint - circle->centre;


	float distanceSquared = circleToClosest.LengthSquared();

	return (distanceSquared <= circle->radius * circle->radius);
	
}

bool Physics::LineVsBox(SLine* line, SBox* box)
{
	SLine edges[4] = {
	   SLine(box->minimum, Vector2(box->maximum.x, box->minimum.y)), // Bottom edge
	   SLine(Vector2(box->maximum.x, box->minimum.y), box->maximum), // Right edge
	   SLine(box->maximum, Vector2(box->minimum.x, box->maximum.y)), // Top edge
	   SLine(Vector2(box->minimum.x, box->maximum.y), box->minimum)  // Left edge
	};

	// Check intersection with each edge
	for (int i = 0; i < 4; i++)
	{
		if (LineVsLine(line, &edges[i])) 
			return true;
	
	}

	return false;
}

bool Physics::CircleVsBox(SCircle* circle, SBox* box)
{

	Vector2 closestPoint =
	{
	  MathF::Max(box->minimum.x, MathF::Min(circle->centre.x, box->maximum.x)),
	  MathF::Max(box->minimum.y, MathF::Min(circle->centre.y, box->maximum.y))
	};


	Vector2 circleToClosest = closestPoint - circle->centre;

	float distanceSquared = circleToClosest.LengthSquared();

	return distanceSquared <= (circle->radius * circle->radius);;
}

bool Physics::Raycast(Collider* colliderToCheck, Vector2 startpoint, Vector2 direction, float distance)
{
	if (!colliderToCheck) return false;

	SLine line = { startpoint,  startpoint + (direction * distance) };


	switch (colliderToCheck->GetShapeType())
	{
	case eShape::BOX: 
		return LineVsBox(&line, &dynamic_cast<BoxCollider*>(colliderToCheck)->GetBox());
	case eShape::CIRCLE:
		return LineVsCircle(&line, &dynamic_cast<CircleCollider*>(colliderToCheck)->GetCircle());
	case eShape::LINE:
		return LineVsLine(&line, &dynamic_cast<LineCollider*>(colliderToCheck)->GetLine());
	}


	return false;
}
