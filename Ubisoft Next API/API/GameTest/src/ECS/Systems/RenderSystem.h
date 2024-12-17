#pragma once

#include "../System.h"
#include "../Components/RenderComponent.h"
class RenderSystem : public ISystem
{
public:

	 void Start() override;
	 void Update(std::vector<Entity*> entities, float deltaTime) override ;
	 void Render(std::vector<Entity*> entities) override;
	 void Cleanups() override;


};

