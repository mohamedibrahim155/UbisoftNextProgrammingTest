#include "stdafx.h"
#include "SpriteSheetRenderer.h"
#include "RenderComponent.h"
#include "App/app.h"
SpriteSheetRenderer::SpriteSheetRenderer(std::string filename, int column, int row) 
	: SpriteRenderer(filename)
{
	this->sprite = CreateSprite(filename, column, row);
}

SpriteSheetRenderer::SpriteSheetRenderer(std::string filename, int column, int row, int spriteOrder)
	: SpriteRenderer(filename)
{
	this->spriteOrder = spriteOrder;

	this->sprite = CreateSprite(filename, column, row);
}

SpriteSheetRenderer::~SpriteSheetRenderer()
{
}

void SpriteSheetRenderer::Start()
{
	SpriteRenderer::Start();
}

void SpriteSheetRenderer::UpdateComponent()
{
	SpriteRenderer::UpdateComponent();
}

void SpriteSheetRenderer::Render()
{
	SpriteRenderer::Render();
}

void SpriteSheetRenderer::SetAnimation(int ID, bool playfromBeginning)
{
	sprite->SetAnimation(ID, playfromBeginning);
}

void SpriteSheetRenderer::CreateAnimation(unsigned int ID, float speed, const std::vector<int>& frames)
{
	sprite->CreateAnimation(ID, speed, frames);
}



