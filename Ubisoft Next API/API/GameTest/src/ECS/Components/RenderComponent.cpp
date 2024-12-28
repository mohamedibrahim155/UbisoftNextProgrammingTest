#include "stdafx.h"
#include "RenderComponent.h"
#include "../../Timer/Timer.h"
#include "../App/app.h"
#include "../src/ECS/Entity.h"

RenderComponent::RenderComponent(std::string filename, Vector2 position) : 
	IComponent(ComponentType::RENDER_COMPONENT), 
    fileName(filename)
{

	centerScreen = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

	offset = position;

}

RenderComponent::RenderComponent(Vector2 offsetPosition) :IComponent(ComponentType::RENDER_COMPONENT)
{
	centerScreen = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
	offset = offsetPosition;
}
RenderComponent::RenderComponent( std::string filename) : 
	IComponent(ComponentType::RENDER_COMPONENT), 
    fileName(filename)
{
	centerScreen = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

}

