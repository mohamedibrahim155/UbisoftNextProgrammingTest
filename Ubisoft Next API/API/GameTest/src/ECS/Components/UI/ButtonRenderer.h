#pragma once
#include "../src/ECS/Component.h"
#include "../src/Events/Event.h"
#include "../src/ECS/Components/Renders/SpriteRenderer.h"
#include "../Collider/BoxCollider.h"
#include "../Collider/CircleCollider.h"
class ButtonRenderer : public SpriteRenderer
{
public:
	ButtonRenderer(std::string filename);
	 ~ButtonRenderer() override = default;

	 // Inherited via RenderComponent
	void start() override;
	void updateComponent() override;
	void render() override;
	int renderOrder() override;
	ButtonRenderer* clone() const override;

	//Events listeners
	void addListenersOnButtonPress(const std::function<void()>& callback);
	void addListenersOnButtonHover(const std::function<void()>& callback);
	void addListenersOnButtonHoverExit(const std::function<void()>& callback);
private:

	bool isOnHover = false;
	
	SCircle mousCircle;
	Transform* transform     = nullptr;
	BoxCollider* boxCollider = nullptr;

	//Events
	CEvent<> OnButtonClick;
	CEvent<> OnButtonHover;
	CEvent<> OnButtonHoverExit;



	Vector2 getMousePosition();

	void DrawCircle(float cx, float cy, float radius, int segments, const Vector3& color);

};

