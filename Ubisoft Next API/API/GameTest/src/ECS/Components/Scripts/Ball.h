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

	RigidBody* rigidBody;
	void createBallSprite();
	void updateInput();
};

