#pragma once
#include "../System.h"
class MovementSystem : public ISystem
{
public:
	MovementSystem() : ISystem("MovementSystem", eSystemType::MOVEMENT_SYSTEM) {};
	// Inherited via ISystem
	void start(std::vector<Entity*> entities) override;
	void update(std::vector<Entity*> entities, float deltaTime) override;
	void render(std::vector<Entity*> entities, bool isDebugVisible) override;
	void cleanups() override;
};

