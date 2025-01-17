#include "stdafx.h"
#include "Camera.h"
#include "../src/ECS/Entity.h"
#include "../src/ECS/Components/Camera/Camera.h"

Camera* ::Camera::m_mainCamera = nullptr;

Camera::Camera() : IComponent(eComponentType::CAMERA_COMPONENT) 
{
}
Camera::~Camera()
{
	if (m_mainCamera)
	{
		m_mainCamera = nullptr;
		delete m_mainCamera;
	}
}
void Camera::start()
{
	gameObject->transform.position = Vector3(centerScreenX, centerScreenY, 0);
}

void Camera::updateComponent()
{

}

void Camera::render(bool isDebugRender)
{
}

void Camera::cleanUp()
{
}

IComponent* Camera::clone() const
{
    return nullptr;
}

Camera* Camera::createCamera()
{
	m_mainCamera = new Camera();
	return m_mainCamera;
}

Camera* Camera::mainCamera()
{
	return m_mainCamera;
}


