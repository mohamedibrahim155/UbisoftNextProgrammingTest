#include "stdafx.h"
#include "LineCollider.h"

LineCollider::LineCollider(const Vector2& startpoint, const Vector2& endpoint) : Collider(eShape::LINE)
{
	m_line.startPoint = startpoint + m_center;
	m_line.endPoint   = endpoint   + m_center;
}

LineCollider::LineCollider() : Collider(eShape::LINE)
{
	m_line.startPoint = m_center;
	m_line.endPoint   = m_center;
}

SBox LineCollider::getBounds()
{
	SLine line = getLine();


	SBox box;

	box.minimum = line.startPoint;
	box.maximum = line.endPoint;

	box.minimum.x *= m_scale.x;
	box.minimum.y *= m_scale.y;

	box.maximum.x *= m_scale.x;
	box.maximum.y *= m_scale.y;


	box.minimum = box.minimum + m_offset;
	box.maximum = box.maximum + m_offset;


	return box;
}

LineCollider* LineCollider::clone() const
{
	return new LineCollider(this->m_line.startPoint, this->m_line.endPoint);
}



void LineCollider::render(bool isDebugVisible)
{

	SLine line = getLine();

	if (!isDebugVisible) return;

	App::DrawLine(line.startPoint.x, line.startPoint.y, line.endPoint.x, line.endPoint.y, m_debugColor.x, m_debugColor.y, m_debugColor.z);
}

void LineCollider::calculateShape()
{

}

SLine LineCollider::getLine()
{
	SLine line = m_line;

	line.startPoint.x *= m_scale.x;
	line.startPoint.y *= m_scale.y;

	line.endPoint.x *= m_scale.x;
	line.endPoint.y *= m_scale.y;

	line.startPoint = line.startPoint + m_offset;
	line.endPoint = line.endPoint + m_offset;


	return line;
}

void LineCollider::setLine(const Vector2& startpoint, const Vector2& endpoint)
{
	m_line.startPoint = startpoint;
	m_line.endPoint = endpoint;

}
