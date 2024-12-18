#include "stdafx.h"
#include "RenderComponent.h"
#include "../../Timer/Timer.h"
#include "../App/app.h"
#include "../src/ECS/Entity.h"

RenderComponent::RenderComponent(std::string filename, Vector2 position) : 
	IComponent(ComponentType::RENDER_COMPONENT), 
    fileName(filename)
{
	//sprite = App::CreateSprite(filename.c_str(), 1, 1);

	centerScreen = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

	spriteOffset = position;

	//sprite->SetPosition(centerScreen.x + spriteOffset.x, centerScreen.y + spriteOffset.y);

}
RenderComponent::RenderComponent(Vector2 offsetPosition) :IComponent(ComponentType::RENDER_COMPONENT)
{
	centerScreen = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
	spriteOffset = offsetPosition;
}
RenderComponent::RenderComponent( std::string filename) : 
	IComponent(ComponentType::RENDER_COMPONENT), 
    fileName(filename)
{
	centerScreen = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

}

