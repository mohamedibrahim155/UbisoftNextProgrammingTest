#pragma once

#include "../System.h"
#include "../Components/Renders/SpriteRenderer.h"
#include "../Components/Renders/SpriteSheetRenderer.h"
#include "../Components/UI/TextRenderer.h"
#include "../Components/UI/ButtonRenderer.h"


struct RenderEntity
{
public:
	EntityID ID;
	Entity* entity;
	RenderComponent* component;

	RenderEntity() = default;

	RenderEntity(EntityID ID,Entity* entity, RenderComponent* component)
		: ID(ID),entity(entity), component(component){}
};
class RenderSystem : public ISystem
{
public:
	RenderSystem() : ISystem("RenderSystem",  eSystemType::RENDER_SYSTEM) {};
	 void start(std::vector<Entity*> entities) override;
	 void update(std::vector<Entity*> entities, float deltaTime) override ;
	
	 void render(std::vector<Entity*> entities) override;
	 void cleanups() override;

private:


	void addEntityToRenders(Entity* entity);
	void removeEntityFromRenders(Entity* entity);

	void updateSprites();
	void updateUIComponents();

	void subscribeEvents();
	void handleOnEntityAdded(Entity* entity);

	std::vector<std::pair<int, RenderEntity*>> m_sortedSprites;
	std::vector<RenderEntity*> m_listOfUIRenderer;
	std::vector<RenderEntity*> m_listOfSpriteRenderers;
};

