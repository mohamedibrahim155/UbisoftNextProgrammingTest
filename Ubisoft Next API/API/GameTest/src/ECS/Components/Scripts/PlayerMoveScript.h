#pragma once
#include "../ScriptComponent.h"

class PlayerMoveScript :public ScriptComponent
{
public:
	PlayerMoveScript();
    ~PlayerMoveScript() override ;
	// Inherited via IComponent
	 void Start() override;
	 void UpdateComponent()  override;
	 void Render() override;

};

