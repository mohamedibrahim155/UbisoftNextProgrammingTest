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

	bool m_showLine = false;
	bool m_canAim = true;

	float m_maxLineThreshold = 100;
	float m_bounceSpeed = 500;

	Vector2 m_centerScreen { APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2 };

	Vector2 m_aimDirection;

	RigidBody* rigidBody;
	SpriteRenderer* ballSprite;
	Collider* circleCollider;


	SLine m_renderLine;

	float calculateBounceSpeed(Vector2 aimDir);
	void createBall();
	void updateInput();
	void handleAim();
	void OnBallRelease();
	void renderLine();
	void restBall();
};

