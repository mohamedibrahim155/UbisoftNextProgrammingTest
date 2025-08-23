#include "stdafx.h"
#include "RenderComponent.h"
#include "../../../Timer/Timer.h"
#include "../App/app.h"
#include "../src/ECS/Entity.h"

RenderComponent::RenderComponent(std::string filename, Vector2 position) : 
	IComponent(eComponentType::RENDER_COMPONENT), 
    m_fileName(filename)
{

	m_centerScreen = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

	m_offset = position;

}

RenderComponent::RenderComponent(Vector2 offsetPosition) :IComponent(eComponentType::RENDER_COMPONENT)
{
	m_centerScreen = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
	m_offset = offsetPosition;
}
RenderComponent::RenderComponent( std::string filename) : 
	IComponent(eComponentType::RENDER_COMPONENT), 
    m_fileName(filename)
{
	m_centerScreen = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

}

