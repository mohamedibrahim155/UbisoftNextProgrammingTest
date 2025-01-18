#pragma once
#include "ScriptComponent.h"
#include "../Collider/CircleCollider.h"
#include "../Rigidbody/RigidBody.h"

class Ball : public BaseScriptComponent
{
public:
	Ball() : BaseScriptComponent() {};
		~Ball() override = default;
  void start() override;
  void updateComponent() override;
  void render(bool isDebugVisible) override;
  void cleanUp() override;

private:

	const std::string ballTexture = ASSET_PATH + "\\Ball\\ball_red_small.png";

	bool showLine = false;
	Vector2 m_centerScreen { APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2 };



	RigidBody* rigidBody;
	SpriteRenderer* ballSprite;
	Collider* circleCollider;


	SLine m_renderLine;

	void createBall();
	void updateInput();
	void handleAim();
	void renderLine();
};

