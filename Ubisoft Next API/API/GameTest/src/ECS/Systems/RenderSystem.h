#pragma once

#include "../System.h"
#include "../Components/Renders/SpriteRenderer.h"
#include "../Components/Renders/SpriteSheetRenderer.h"
#include "../Components/UI/TextRenderer.h"
#include "../Components/UI/ButtonRenderer.h"
class RenderSystem : public ISystem
{
public:
	RenderSystem() : ISystem("RenderSystem",  eSystemType::RENDER_SYSTEM) {};
	 void start(std::vector<Entity*> entities) override;
	 void update(std::vector<Entity*> entities, float deltaTime) override ;
	 void render(std::vector<Entity*> entities) override;
	 void cleanups() override;

private:

	std::vector<std::pair<int, Entity*>> sortedEntities;

	/*
	TODO : 
	add List of Sprite Renders
	add List of UI's renders
		

	*/
};

