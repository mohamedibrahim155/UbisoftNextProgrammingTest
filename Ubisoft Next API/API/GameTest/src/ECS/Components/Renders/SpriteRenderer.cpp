#include "stdafx.h"
#include "SpriteRenderer.h"
#include "App/app.h"
#include "../src/Utils/Utils.h"




SpriteRenderer::SpriteRenderer(std::string filename, bool createSprite) : RenderComponent(filename)
{
	m_offset = Vector2::Zero();

	if (createSprite)
		m_sprite = this->createSprite(filename, 1, 1);

}
SpriteRenderer::SpriteRenderer(std::string filename, Vector2 offset) :
	RenderComponent(filename)


{
	this->m_offset = offset;
	m_spriteOrder = 0;
	m_sprite = createSprite(filename,1,1);
}

SpriteRenderer::SpriteRenderer(std::string filename, Vector2 offset, int order) : 
	RenderComponent(filename)

{
	this->m_offset = offset;
	m_spriteOrder = order;
	m_sprite = createSprite(filename, 1, 1);
}
SpriteRenderer::~SpriteRenderer()
{
	delete m_sprite;
}

void SpriteRenderer::start()
{

}

void SpriteRenderer::updateComponent()
{
	if (!m_isEnabled) return;

	m_sprite->Update(Timer::GetInstance().deltaTime * 1000);

}

void SpriteRenderer::render()
{
	if (!m_isEnabled) return;

	m_sprite->Draw();
	
}

int SpriteRenderer::renderOrder()
{
	return m_spriteOrder;
}

void SpriteRenderer::setColor(const Vector3&  color)
{
	if (m_sprite == nullptr) return;

	m_sprite->SetColor(color.x, color.y, color.y);
}

void SpriteRenderer::setColor(const float& r, const float& g, const float& b)
{
	if (m_sprite == nullptr) return;
	m_sprite->SetColor(r, g, b);
}

void SpriteRenderer::setPosition(const Vector3&  position)
{
	Vector3 adjustedPosition = Vector3(m_centerScreen.x, m_centerScreen.y, 0);

	adjustedPosition +=  (position + m_offset);

	m_sprite->SetPosition(adjustedPosition.x, adjustedPosition.y);
}

void SpriteRenderer::setRotation(const float& rotationY)
{
	m_sprite->SetAngle(rotationY);
}

void SpriteRenderer::setOffset(const Vector2& offset)
{
	this->m_offset = offset;
}

void SpriteRenderer::setScale(const Vector2& scale)
{
	float max = MathF::Max(scale.x, scale.y);
	m_sprite->SetScale(max);
}

void SpriteRenderer::setOrder(int order)
{
	m_spriteOrder = order;
}

int SpriteRenderer::getSpriteOrder() const
{
	return m_spriteOrder;
}

Vector3 SpriteRenderer::getColor() const
{
	return m_color;
}

CSimpleSprite* SpriteRenderer::getSprite() const
{
	return m_sprite;
}

std::string SpriteRenderer::getFileName() const
{
	return m_fileName;
}

CSimpleSprite* SpriteRenderer::createSprite(std::string filename, int column, int rows)
{
	return App::CreateSprite(filename.c_str(), column, rows);
}

SpriteRenderer* SpriteRenderer::clone() const
{
	return new SpriteRenderer(this->m_fileName,this->m_offset);
}
