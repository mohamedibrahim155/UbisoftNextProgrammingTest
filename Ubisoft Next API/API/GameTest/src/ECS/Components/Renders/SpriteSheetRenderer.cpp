#include "stdafx.h"
#include "SpriteSheetRenderer.h"
#include "RenderComponent.h"
#include "App/app.h"
SpriteSheetRenderer::SpriteSheetRenderer(std::string filename, int column, int row) 
	: SpriteRenderer(filename), 
	m_column(column),
	m_row(row)
{
	this->m_sprite = createSprite(filename, column, row);
}





SpriteSheetRenderer::SpriteSheetRenderer(std::string filename, int column, int row, int spriteOrder)
	: SpriteRenderer(filename) ,
	m_column(column),
	m_row(row)
{
	this->m_spriteOrder = spriteOrder;

	this->m_sprite = createSprite(filename, column, row);
}

SpriteSheetRenderer::~SpriteSheetRenderer()
{
}

void SpriteSheetRenderer::start()
{
	SpriteRenderer::start();
}

void SpriteSheetRenderer::updateComponent()
{
	SpriteRenderer::updateComponent();
}

void SpriteSheetRenderer::render()
{
	SpriteRenderer::render();
}

SpriteSheetRenderer* SpriteSheetRenderer::clone() const
{
	return new SpriteSheetRenderer(this->m_fileName,this->m_column, this->m_row);
}

void SpriteSheetRenderer::setAnimation(int ID, bool playfromBeginning)
{
	m_sprite->SetAnimation(ID, playfromBeginning);
}

void SpriteSheetRenderer::createAnimation(unsigned int ID, float speed, const std::vector<int>& frames)
{
	m_sprite->CreateAnimation(ID, speed, frames);
}



