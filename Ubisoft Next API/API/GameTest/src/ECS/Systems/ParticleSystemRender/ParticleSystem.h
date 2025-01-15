#pragma once
#include "../../System.h"
#include "../src/ECS/Components/Particle/ParticleComponent.h"
class ParticleSystem : public ISystem
{
public:

	ParticleSystem() : ISystem("Particle System", eSystemType::PARTILCE_SYSTEM) {};

	~ParticleSystem() override = default;
	// Inherited via ISystem
	void start(std::vector<Entity*> entities) override;

	void AddParticle(Entity* entity);

	void update(std::vector<Entity*> entities, float deltaTime) override;

	void render(std::vector<Entity*> entities, bool isDebugVisible) override;

	void cleanups() override;

private:

	std::vector<std::pair<Entity*, ParticleComponent* >> listOfParticleComponents;
};

