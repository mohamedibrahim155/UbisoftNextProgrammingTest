#include "stdafx.h"
#include "SpriteRenderer.h"
#include "App/app.h"
#include "../src/Utils/Utils.h"




SpriteRenderer::SpriteRenderer(std::string filename, bool createSprite) : RenderComponent(filename)
{
	offset = Vector2::Zero();

	if (createSprite)
		sprite = this->createSprite(filename, 1, 1);

}
SpriteRenderer::SpriteRenderer(std::string filename, Vector2 offset) :
	RenderComponent(filename)


{
	this->offset = offset;
	spriteOrder = 0;
	sprite = createSprite(filename,1,1);
}

SpriteRenderer::SpriteRenderer(std::string filename, Vector2 offset, int order) : 
	RenderComponent(filename)

{
	this->offset = offset;
	spriteOrder = order;
	sprite = createSprite(filename, 1, 1);
}
SpriteRenderer::~SpriteRenderer()
{
	delete sprite;
}

void SpriteRenderer::start()
{

}

void SpriteRenderer::updateComponent()
{
	if (!isComponentEnabled) return;

	sprite->Update(Timer::GetInstance().deltaTime * 1000);

}

void SpriteRenderer::render()
{
	if (!isComponentEnabled) return;

	sprite->Draw();
	
}

int SpriteRenderer::renderOrder()
{
	return spriteOrder;
}

void SpriteRenderer::setColor(const Vector3&  color)
{
	if (sprite == nullptr) return;

	sprite->SetColor(color.x, color.y, color.y);
}

void SpriteRenderer::setColor(const float& r, const float& g, const float& b)
{
	if (sprite == nullptr) return;
	sprite->SetColor(r, g, b);
}

void SpriteRenderer::setPosition(const Vector3&  position)
{
	Vector3 adjustedPosition = Vector3(centerScreen.x, centerScreen.y, 0);

	adjustedPosition +=  (position + offset);

	sprite->SetPosition(adjustedPosition.x, adjustedPosition.y);
}

void SpriteRenderer::setRotation(const float& rotationY)
{
	sprite->SetAngle(rotationY);
}

void SpriteRenderer::setOffset(const Vector2& offset)
{
	this->offset = offset;
}

void SpriteRenderer::setScale(const Vector2& scale)
{
	float max = MathF::Max(scale.x, scale.y);
	sprite->SetScale(max);
}

void SpriteRenderer::setOrder(int order)
{
	spriteOrder = order;
}

int SpriteRenderer::getSpriteOrder() const
{
	return spriteOrder;
}

Vector3 SpriteRenderer::getColor() const
{
	return color;
}

CSimpleSprite* SpriteRenderer::getSprite() const
{
	return sprite;
}

std::string SpriteRenderer::getFileName() const
{
	return fileName;
}

CSimpleSprite* SpriteRenderer::createSprite(std::string filename, int column, int rows)
{
	return App::CreateSprite(filename.c_str(), column, rows);
}

SpriteRenderer* SpriteRenderer::clone() const
{
	return new SpriteRenderer(this->fileName,this->offset);
}
