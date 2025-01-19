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
	void update(std::vector<Entity*> entities, float deltaTime) override;
	void render(std::vector<Entity*> entities, bool isDebugVisible) override;
	void cleanups() override;

private:

	std::unordered_map<EntityID,ParticleComponent* > listOfParticleComponents;

	void handleOnEntityAdded(Entity* entity);
	void handleOnEntityRemoved(Entity* entity);
	void addParticle(Entity* entity);
};

