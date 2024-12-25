#pragma once
#include "../System.h"
#include "../src/ECS/Components/SpriteRenderer.h"
class MovementSystem : public ISystem
{
public:
	MovementSystem() : ISystem("MovementSystem", eSystemType::MOVEMENT_SYSTEM) {};
	// Inherited via ISystem
	void Start(std::vector<Entity*> entities) override;
	void Update(std::vector<Entity*> entities, float deltaTime) override;
	void Render(std::vector<Entity*> entities) override;
	void Cleanups() override;
};

