#include "stdafx.h"
#include "LineCollider.h"

LineCollider::LineCollider(const Vector2& startpoint, const Vector2& endpoint) : Collider(eShape::LINE)
{
	m_line.startPoint = startpoint + center;
	m_line.endPoint = endpoint + center;
}

SBox LineCollider::GetBounds()
{
	SLine line = GetLine();


	SBox box;

	box.minimum = line.startPoint;
	box.maximum = line.endPoint;

	box.minimum.x *= mScale.x;
	box.minimum.y *= mScale.y;

	box.maximum.x *= mScale.x;
	box.maximum.y *= mScale.y;


	box.minimum = box.minimum + offset;
	box.maximum = box.maximum + offset;


	return box;
}

LineCollider* LineCollider::Clone() const
{
	return new LineCollider(this->m_line.startPoint, this->m_line.endPoint);
}



void LineCollider::Render()
{

	SLine line = GetLine();



	const Vector3 color{ 0,1,0 };
	App::DrawLine(line.startPoint.x, line.startPoint.y, line.endPoint.x, line.endPoint.y, color.x, color.y, color.z);
}

void LineCollider::CalculateShape()
{

}

SLine LineCollider::GetLine()
{
	SLine line = m_line;

	line.startPoint.x *= mScale.x;
	line.startPoint.y *= mScale.y;

	line.endPoint.x *= mScale.x;
	line.endPoint.y *= mScale.y;

	line.startPoint = line.startPoint + offset;
	line.endPoint = line.endPoint + offset;


	return line;
}

void LineCollider::SetLine(const Vector2& startpoint, const Vector2& endpoint)
{
	m_line.startPoint = startpoint;
	m_line.endPoint = endpoint;

}
