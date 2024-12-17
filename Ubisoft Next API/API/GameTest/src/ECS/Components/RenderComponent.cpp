#include "stdafx.h"
#include "RenderComponent.h"
#include "../../Timer/Timer.h"
#include "../App/app.h"

RenderComponent::RenderComponent( std::string filename) : IComponent(ComponentType::RENDER_COMPONENT), fileName(filename)
{
	sprite = App::CreateSprite(filename.c_str(),1,1);
	sprite->SetPosition(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
}

void RenderComponent::UpdateComponent()
{
	if (!isComponentEnabled) return;

	if (!sprite) return;

	sprite->Update(Timer::GetInstance().deltaTime * 1000);
}

CSimpleSprite* RenderComponent::GetSprite()
{
	return sprite;
}

void RenderComponent::Render()
{
	if (!isComponentEnabled) return;
	if (!sprite) return;

	sprite->Draw();
}




RenderComponent::~RenderComponent()
{
	if(sprite)
	delete sprite;
}

void RenderComponent::Initialise()
{
	
}
