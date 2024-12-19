#include "stdafx.h"
#include "SpriteRenderer.h"
#include "App/app.h"
#include "../src/Utils/Utils.h"




SpriteRenderer::SpriteRenderer(std::string filename) : RenderComponent(filename)
{
	spriteOffset = Vector2::Zero();
	spritePosition = Vector3::Zero();
}

SpriteRenderer::SpriteRenderer(std::string filename, Vector3 position, Vector2 offset) : 
	RenderComponent(filename)


{
	sprite = CreateSprite(filename,1,1);
	spriteOffset = offset;
	spritePosition = position + offset;
	spriteOrder = 0;
	SetPosition(position + offset);
}

SpriteRenderer::SpriteRenderer(std::string filename, Vector3 position, Vector2 offset, int order) : 
	RenderComponent(filename)

{
	sprite = CreateSprite(filename, 1, 1);
	spriteOffset = offset;
	spritePosition = position + offset;
	spriteOrder = order;

	SetPosition(position + offset);
//	sprite->SetPosition(centerScreen.x + position.x + spriteOffset.x, centerScreen.y + position.y + spriteOffset.y);
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

void SpriteRenderer::SetColor(const Vector3&  color)
{
	if (sprite == nullptr) return;

	sprite->SetColor(color.x, color.y, color.y);
}

void SpriteRenderer::SetPosition(const Vector3&  position)
{
	Vector3 adjustedPosition = Vector3(centerScreen.x, centerScreen.y, 0);

	adjustedPosition +=  (position + spriteOffset);
	//spritePosition = adjustedPosition + position + spriteOffset;

	sprite->SetPosition(adjustedPosition.x, adjustedPosition.y);
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
