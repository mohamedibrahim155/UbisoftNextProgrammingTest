#include "stdafx.h"
#include "PhysicsUtils.h"
#include "../src/ECS/Components/Collider/CircleCollider.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/ECS/Components/Collider/LineCollider.h"
bool Physics::CheckCollision(Collider* colliderA, Collider* colliderB, std::vector<Vector2>& collisionPt, std::vector<Vector2>& collisionNormal)
{
	// Checking AABB collision 
	if (BoxVsBox(&colliderA->getBounds(), &colliderB->getBounds(), collisionPt, collisionNormal))
	{
		switch (colliderA->GetShapeType())
		{

#pragma region CircleVS


		case eShape::CIRCLE:


			switch (colliderB->GetShapeType())
			{
			case eShape::CIRCLE:

				return CircleVsCircle(&dynamic_cast<CircleCollider*>(colliderA)->getCircle(),
					&dynamic_cast<CircleCollider*>(colliderB)->getCircle(), collisionPt,collisionNormal);

			case eShape::BOX:

				return CircleVsBox(&dynamic_cast<CircleCollider*>(colliderA)->getCircle(),
					&dynamic_cast<BoxCollider*>(colliderB)->getBox(),true ,collisionPt, collisionNormal);


			case eShape::LINE:

				return LineVsCircle(&dynamic_cast<LineCollider*>(colliderB)->getLine(),
					&dynamic_cast<CircleCollider*>(colliderA)->getCircle());
			}

			break;
#pragma endregion

#pragma region BoxVS
		case eShape::BOX:

			switch (colliderB->GetShapeType())
			{

			case eShape::CIRCLE:
				return CircleVsBox(&dynamic_cast<CircleCollider*>(colliderB)->getCircle(),
					&dynamic_cast<BoxCollider*>(colliderA)->getBox(), false, collisionPt, collisionNormal);

			case eShape::BOX:

				return BoxVsBox(&dynamic_cast<BoxCollider*>(colliderA)->getBox(),
					&dynamic_cast<BoxCollider*>(colliderB)->getBox(), collisionPt, collisionNormal);


			case eShape::LINE:
				return LineVsBox(&dynamic_cast<LineCollider*>(colliderB)->getLine(),
					&dynamic_cast<BoxCollider*>(colliderA)->getBox());
			}

			break;

#pragma endregion

#pragma region LineVs

		case eShape::LINE:

			switch (colliderB->GetShapeType())
			{


			case eShape::CIRCLE:


				return LineVsCircle(&dynamic_cast<LineCollider*>(colliderA)->getLine(),
					&dynamic_cast<CircleCollider*>(colliderB)->getCircle());

			case eShape::BOX:

				return LineVsBox(&dynamic_cast<LineCollider*>(colliderA)->getLine(),
					&dynamic_cast<BoxCollider*>(colliderB)->getBox());


			case eShape::LINE:

				return LineVsLine(&dynamic_cast<LineCollider*>(colliderA)->getLine(),
					&dynamic_cast<LineCollider*>(colliderB)->getLine());
			}

			break;
#pragma endregion

		}

	}

	return false;
}

bool Physics::CircleVsCircle(SCircle* circleA, SCircle* circleB, std::vector<Vector2>& collisionPt, std::vector<Vector2>& collisionNormal)
{
	float radius = circleA->radius + circleB->radius;

	Vector2 diff = circleB->centre - circleA->centre;
	float dot = diff.x * diff.x + diff.y * diff.y;

	Vector2 collisionNr;
	Vector2 collisionPnt;

	if (dot <= radius *  radius)
	{
		if (dot != 0)
		{
			collisionNr = diff.Normalize();
		}
		else
		{
			collisionNr = Vector2::One().Normalize();
		}


		collisionPnt = circleA->centre + (collisionNr * circleA->radius);

		collisionPt.push_back(collisionPnt);
		collisionNormal.push_back(collisionNr);

		return true;
	}

	return false;
}

bool Physics::BoxVsBox(SBox* boxA, SBox* boxB, std::vector<Vector2>& collisionPt, std::vector<Vector2>& collisionNormal)
{
	if (boxA->maximum[0] <  boxB->minimum[0] || boxA->minimum[0] > boxB->maximum[0]) return false;
	if (boxA->maximum[1] <  boxB->minimum[1] || boxA->minimum[1] > boxB->maximum[1]) return false;

	SBox instersectionAABB;

	for (int i = 0; i < 2; i++)
	{
		instersectionAABB.minimum[i] = MathF::Max(boxA->minimum[i], boxB->minimum[i]);

		instersectionAABB.maximum[i] = MathF::Min(boxA->maximum[i], boxB->maximum[i]);
	}
	Vector2 collisionpt = instersectionAABB.GetCenter();

	collisionPt.push_back(collisionpt);

	Vector2 centerA = boxA->GetCenter();
	Vector2 centerB = boxB->GetCenter();

	Vector2 collisionNr = centerA - centerB;

	collisionNr = collisionNr.Normalize();

	collisionNormal.push_back(collisionNr);
	return true;
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

bool Physics::CircleVsBox(SCircle* circle, SBox* box , bool isCircle, std::vector<Vector2>& collisionPt, std::vector<Vector2>& collisionNormal)
{


	float sqDist =  SqDistPointAABB(circle->centre, box);

	float sqRadius = circle->radius * circle->radius;


	if (sqDist <= sqRadius)
	{
		Vector2 collisionPoint = ClosestPtAABB(circle->centre, box);

		Vector2 collisionNr = Vector2::Zero();

		if (isCircle)
		{
			collisionNr = collisionPoint - circle->centre;
		}
		else
		{
			collisionNr = collisionPoint - box->GetCenter();

			collisionNr = collisionNr.Normalize();
		}

		collisionPt.push_back(collisionPoint);
		collisionNormal.push_back(collisionNr);

		return true;
	}

	return false;
}

bool Physics::Raycast(Collider* colliderToCheck, Vector2 startpoint, Vector2 direction, float distance)
{
	if (!colliderToCheck) return false;

	SLine line = { startpoint,  startpoint + (direction * distance) };


	switch (colliderToCheck->GetShapeType())
	{
	case eShape::BOX: 
		return LineVsBox(&line, &dynamic_cast<BoxCollider*>(colliderToCheck)->getBox());
	case eShape::CIRCLE:
		return LineVsCircle(&line, &dynamic_cast<CircleCollider*>(colliderToCheck)->getCircle());
	case eShape::LINE:
		return LineVsLine(&line, &dynamic_cast<LineCollider*>(colliderToCheck)->getLine());
	}


	return false;
}




float Physics::SqDistPointAABB(Vector2 point,  SBox* b)
{
	float sqDist = 0;

	for (int i = 0; i < 2; i++)
	{
		float p = point[i];

		if (p < b->minimum[i])
		{
			sqDist += (b->minimum[i] - p) * (b->minimum[i] - p);
		}
		if (p > b->maximum[i])
		{
			sqDist += (p - b->maximum[i]) * (p - b->maximum[i]);
		}

	}

	return sqDist;
}

const Vector2& Physics::ClosestPtAABB(Vector2& point, SBox* b)
{
	Vector2 q;

	for (int i = 0; i < 2; i++) {
		float v = point[i];
		if (v < b->minimum[i]) v = b->minimum[i]; // v = max(v, b.min[i])
		if (v > b->maximum[i]) v = b->maximum[i]; // v = min(v, b.max[i])
		q[i] = v;
	}
	return q;
}


