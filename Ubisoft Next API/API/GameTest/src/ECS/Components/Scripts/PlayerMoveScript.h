#pragma once
#include "ScriptComponent.h"
#include "../src/ECS/Components/Renders/SpriteSheetRenderer.h"


class PlayerMoveScript :public ScriptComponentBase
{
public:
	PlayerMoveScript();
    ~PlayerMoveScript() override ;
	// Inherited via IComponent
	 void start() override;
	 void updateComponent()  override;
	 void render() override;

	 SpriteSheetRenderer* spriteSheet;

	 // Inherited via ScriptComponent
	 PlayerMoveScript* clone() const override;
};

