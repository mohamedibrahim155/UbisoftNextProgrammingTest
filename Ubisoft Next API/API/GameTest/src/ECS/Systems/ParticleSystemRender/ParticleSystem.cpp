#include "stdafx.h"
#include "ParticleSystem.h"
#include "../src/ECS/SystemManager.h"
void ParticleSystem::start()
{
	m_systemManager->OnEntityAdded.Subscribe([this] (Entity* entity)
		{
			handleOnEntityAdded(entity);
		});

	m_systemManager->OnEntityRemoved.Subscribe([this](Entity* entity)
		{
			handleOnEntityRemoved(entity);
		});
}

void ParticleSystem::handleOnEntityAdded(Entity* entity)
{
	entity->OnComponentAdded.Subscribe([this, entity](IComponent* components)
		{
			if (components->getComponentType() == eComponentType::PARTICLE_COMPONENT)
			{
				addParticle(entity);
			}
		});
}

void ParticleSystem::handleOnEntityRemoved(Entity* entity)
{

	EntityID ID = entity->getID();

	listOfParticleComponents.erase(ID);
}

void ParticleSystem::addParticle(Entity* entity)
{
	ParticleComponent* particleComponent = (ParticleComponent*)entity->getComponent(eComponentType::PARTICLE_COMPONENT);
	if (particleComponent)
	{
		listOfParticleComponents[entity->getID()] = particleComponent;
	}
}

void ParticleSystem::update(std::vector<Entity*> entities, float deltaTime)
{
	for (std::pair<EntityID,ParticleComponent*> item : listOfParticleComponents)
	{
		ParticleComponent* particle = item.second;

		if (!particle->m_isStartInvoked)
		{
			particle->start();
			particle->m_isStartInvoked = true;
			continue;
		}


		particle->updateComponent();
	}
}

void ParticleSystem::render( bool isDebugVisible)
{
	for (std::pair<EntityID, ParticleComponent*> item : listOfParticleComponents)
	{
		ParticleComponent* particle = item.second;

		particle->render(isDebugVisible);
	}

}

void ParticleSystem::cleanups()
{
	listOfParticleComponents.clear();
}
