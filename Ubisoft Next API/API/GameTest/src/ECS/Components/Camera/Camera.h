#pragma once
#include "../src/ECS/Component.h"
class Camera : public IComponent
{
public:

	Camera();

	~Camera() override;
	// Inherited via IComponent

	void start() override;
	void updateComponent() override;
	void render(bool isDebugRender) override;
	void cleanUp() override;
	IComponent* clone() const override;

	static Camera* createCamera();
	static Camera* mainCamera();

private:

	float centerScreenX = APP_VIRTUAL_WIDTH * 0.5f;
	float centerScreenY = APP_VIRTUAL_HEIGHT * 0.5f;

	static Camera* m_mainCamera;
};

