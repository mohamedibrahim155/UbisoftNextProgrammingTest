#pragma once
#include "../src/ECS/Component.h"
#include "../src/Events/Event.h"
#include "../src/ECS/Components/Renders/SpriteRenderer.h"
#include  "TextRenderer.h"
#include "../Collider/BoxCollider.h"
class ButtonRenderer : public SpriteRenderer
{
public:
	ButtonRenderer(std::string filename);
	ButtonRenderer(std::string filename, TextRenderer* textComponent);
	 ~ButtonRenderer() override = default;

	 // Inherited via RenderComponent
	void start() override;
	void updateComponent() override;
	void render() override;
	void cleanUp() override;
	int renderOrder() override;
	ButtonRenderer* clone() const override;

	//Events listeners
	void addListenersOnButtonPress(const std::function<void()>& callback);
	void addListenersOnButtonHover(const std::function<void()>& callback);
	void addListenersOnButtonHoverExit(const std::function<void()>& callback);
	void cleanEvents();

	void setTextColor(float r, float g, float b);
	void setText(const std::string& message);
private:

	bool isOnHover = false;
	bool m_isTextEnabled = false;
	SCircle mousCircle;
	Transform* transform     = nullptr;
	BoxCollider* boxCollider = nullptr;
	TextRenderer* textComponent;

	//Events
	CEvent<> OnButtonClick;
	CEvent<> OnButtonHover;
	CEvent<> OnButtonHoverExit;

	Vector2 getMousePosition();

	bool IsMousePressed(const int mouseKey);
    std::unordered_map<int, bool> previousMouseKeyStates;

	
};

