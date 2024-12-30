#pragma once
#include "../System.h"
class MovementSystem : public ISystem
{
public:
	MovementSystem() : ISystem("MovementSystem", eSystemType::MOVEMENT_SYSTEM) {};
	// Inherited via ISystem
	void start(std::vector<Entity*> entities) override;
	void Update(std::vector<Entity*> entities, float deltaTime) override;
	void render(std::vector<Entity*> entities) override;
	void Cleanups() override;
};

