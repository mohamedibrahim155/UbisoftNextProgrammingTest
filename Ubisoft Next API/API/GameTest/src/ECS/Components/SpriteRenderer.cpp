#include "stdafx.h"
#include "SpriteRenderer.h"
#include "App/app.h"
#include "../src/Utils/Utils.h"




SpriteRenderer::SpriteRenderer(std::string filename) : RenderComponent(filename)
{
	spriteOffset = Vector2::Zero();
}

SpriteRenderer::SpriteRenderer(std::string filename, Vector2 offset) : 
	RenderComponent(filename)


{
	spriteOffset = offset;
	spriteOrder = 0;
	sprite = CreateSprite(filename,1,1);
}

SpriteRenderer::SpriteRenderer(std::string filename, Vector2 offset, int order) : 
	RenderComponent(filename)

{
	spriteOffset = offset;
	spriteOrder = order;
	sprite = CreateSprite(filename, 1, 1);
}
SpriteRenderer::~SpriteRenderer()
{
	delete sprite;
}

void SpriteRenderer::Start()
{

}

void SpriteRenderer::UpdateComponent()
{
	if (!isComponentEnabled) return;

	sprite->Update(Timer::GetInstance().deltaTime * 1000);

}

void SpriteRenderer::Render()
{
	if (!isComponentEnabled) return;

	sprite->Draw();
	
}

int SpriteRenderer::RenderOrder()
{
	return spriteOrder;
}

void SpriteRenderer::SetColor(const Vector3&  color)
{
	if (sprite == nullptr) return;

	sprite->SetColor(color.x, color.y, color.y);
}

void SpriteRenderer::SetColor(const float& r, const float& g, const float& b)
{
	if (sprite == nullptr) return;
	sprite->SetColor(r, g, b);
}

void SpriteRenderer::SetPosition(const Vector3&  position)
{
	Vector3 adjustedPosition = Vector3(centerScreen.x, centerScreen.y, 0);

	adjustedPosition +=  (position + spriteOffset);

	sprite->SetPosition(adjustedPosition.x, adjustedPosition.y);
}

void SpriteRenderer::SetOffset(const Vector2& offset)
{
	this->spriteOffset = offset;
}

void SpriteRenderer::SetScale(const Vector2& scale)
{
	float max = MathF::Max(scale.x, scale.y);
	sprite->SetScale(max);
}

void SpriteRenderer::SetOrder(int order)
{
	spriteOrder = order;
}

int SpriteRenderer::GetSpriteOrder() const
{
	return spriteOrder;
}

Vector3 SpriteRenderer::GetColor() const
{
	return color;
}

CSimpleSprite* SpriteRenderer::GetSprite() const
{
	return sprite;
}

CSimpleSprite* SpriteRenderer::CreateSprite(std::string filename, int column, int rows)
{
	return App::CreateSprite(filename.c_str(), column, rows);
}
