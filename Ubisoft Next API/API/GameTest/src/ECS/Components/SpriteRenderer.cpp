#include "stdafx.h"
#include "SpriteRenderer.h"
#include "App/app.h"
#include "../src/Utils/Utils.h"


SpriteRenderer::SpriteRenderer(std::string filename, Vector3 position, Vector2 offset) : RenderComponent(filename)


{
	sprite = App::CreateSprite(filename.c_str(), 1, 1);
	spriteOffset = offset;
	spritePosition = position;
	//sprite->SetPosition(centerScreen.x + position.x + spriteOffset.x, centerScreen.y + position.y + spriteOffset.y);
	SetPosition(spritePosition);
}

SpriteRenderer::SpriteRenderer(std::string filename, Vector3 position, Vector2 offset, int order) : 
	RenderComponent(filename)

{
	sprite = App::CreateSprite(filename.c_str(), 1, 1);
	spriteOffset = offset;
	spritePosition = position + offset;
	spriteOrder = order;

	SetPosition(spritePosition);
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
	Vector3 centreScreenVec3 = Vector3(centerScreen.x, centerScreen.y, 0);

	spritePosition = centreScreenVec3 + position + spriteOffset;

	sprite->SetPosition(spritePosition.x, spritePosition.y);
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
