#include "stdafx.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider() : Collider(eShape::BOX)
{
	mBox.minimum = { -1, -1 };
	mBox.maximum = { 1, 1 };
}

BoxCollider::BoxCollider(SpriteRenderer* spriteRenderer)
	: Collider(eShape::BOX)
{

	this->spriteRenderer = spriteRenderer;
	mBox.minimum = { -1, -1 };
	mBox.maximum = { 1, 1 };

	calculateShape();
}



SBox BoxCollider::getBounds()
{
	return getBox();
}

void BoxCollider::calculateShape()
{


	if (spriteRenderer)
	{
		width = spriteRenderer->getSprite()->GetWidth();
		height = spriteRenderer->getSprite()->GetHeight();
	}

	float extendX = width * 0.5f;
	float extendY = height * 0.5f;

	mBox.minimum = { -extendX, -extendY };
	mBox.maximum = { extendX, extendY };

}

SBox BoxCollider::getBox()
{
	SBox box = this->mBox;

	box.minimum.x *= mScale.x;
	box.minimum.y *= mScale.y;

	box.maximum.x *= mScale.x;
	box.maximum.y *= mScale.y;

	if (transform)
	{
		box.minimum.x *= transform->scale.x;
		box.minimum.y *= transform->scale.y;
		
		box.maximum.x *= transform->scale.x;
		box.maximum.y *= transform->scale.y;
		
		
		box.minimum.x += transform->position.x  + center.x;
		box.minimum.y += transform->position.y  + center.y;
		
		box.maximum.x += transform->position.x + center.x;
		box.maximum.y += transform->position.y + center.y;
	}

	box.minimum = box.minimum + offset;
	box.maximum = box.maximum + offset;


	return box;
}

BoxCollider* BoxCollider::clone() const
{
	return new BoxCollider();
}




void BoxCollider::render()
{
	SBox box = getBox();

	float topLeftX = box.minimum.x;
	float topLeftY = box.maximum.y;

	float topRightX = box.maximum.x;
	float topRightY = box.maximum.y;

	float bottomLeftX = box.minimum.x;
	float bottomLeftY = box.minimum.y;

	float bottomRightX = box.maximum.x;
	float bottomRightY = box.minimum.y;

	Vector3 color = Vector3(0, 1, 0);

	App::DrawLine(topLeftX, topLeftY, topRightX, topRightY, color.x, color.y, color.z);
	App::DrawLine(topRightX, topRightY, bottomRightX, bottomRightY, color.x, color.y, color.z);
	App::DrawLine(bottomRightX, bottomRightY, bottomLeftX, bottomLeftY, color.x, color.y, color.z);
	App::DrawLine(bottomLeftX, bottomLeftY, topLeftX, topLeftY, color.x, color.y, color.z);
}
