#pragma once
#include "../src/ECS/Component.h"
#include "../src/Events/Event.h"
#include "../src/ECS/Components/RenderComponent.h"
#include "../Collider/BoxCollider.h"
#include "../Collider/CircleCollider.h"
class ButtonRenderer : public SpriteRenderer
{
public:
	ButtonRenderer(std::string filename);
	 ~ButtonRenderer() override = default;

	 // Inherited via RenderComponent
	void Start() override;
	void UpdateComponent() override;
	void Render() override;
	int RenderOrder() override;
	ButtonRenderer* Clone() const override;

	//Events listeners
	void AddListenersOnButtonPress(const std::function<void()>& callback);
	void AddListenersOnButtonHover(const std::function<void()>& callback);
	void AddListenersOnButtonHoverExit(const std::function<void()>& callback);
private:

	bool isOnHover = false;
	
	SCircle mousCircle;
	Transform* transform     = nullptr;
	BoxCollider* boxCollider = nullptr;

	//Events
	CEvent<> OnButtonClick;
	CEvent<> OnButtonHover;
	CEvent<> OnButtonHoverExit;



	Vector2 GetMousePosition();

	void DrawCircle(float cx, float cy, float radius, int segments, const Vector3& color);

};

