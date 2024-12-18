#pragma once

#include "../System.h"
#include "../Components/RenderComponent.h"
#include "../Components/SpriteRenderer.h"
class RenderSystem : public ISystem
{
public:
	RenderSystem() : ISystem("RenderSystem") {};
	 void Start() override;
	 void Update(std::vector<Entity*> entities, float deltaTime) override ;
	 void Render(std::vector<Entity*> entities) override;
	 void Cleanups() override;

private:

};

