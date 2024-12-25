#pragma once
#include "../ScriptComponent.h"
#include "../SpriteSheetRenderer.h"


class PlayerMoveScript :public ScriptComponent
{
public:
	PlayerMoveScript();
    ~PlayerMoveScript() override ;
	// Inherited via IComponent
	 void Start() override;
	 void UpdateComponent()  override;
	 void Render() override;

	 SpriteSheetRenderer* spriteSheet;

	 // Inherited via ScriptComponent
	 PlayerMoveScript* Clone() const override;
};

