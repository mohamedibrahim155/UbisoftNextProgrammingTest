#include "stdafx.h"
#include "ParticleSystem.h"
#include "../src/ECS/SystemManager.h"
void ParticleSystem::start(std::vector<Entity*> entities)
{
	m_systemManager->OnEntityAdded.Subscribe([this] (Entity* entity)
		{
			handleOnEntityAdded(entity);
		});

	m_systemManager->OnEntityRemoved.Subscribe([this](Entity* entity)
		{
			listOfParticleComponents.erase(std::remove_if(listOfParticleComponents.begin(), listOfParticleComponents.end(), [entity](std::pair<Entity*, ParticleComponent*> pair)
				{
					if (pair.first == entity)
					{
						pair.second->cleanUp();
						return true;
					}
					else
					{
						return false;
					}
				}), listOfParticleComponents.end());
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

void ParticleSystem::addParticle(Entity* entity)
{
	ParticleComponent* particleComponent = (ParticleComponent*)entity->getComponent(eComponentType::PARTICLE_COMPONENT);
	if (particleComponent)
	{
		listOfParticleComponents.push_back(std::make_pair(entity, particleComponent));
	}
}

void ParticleSystem::update(std::vector<Entity*> entities, float deltaTime)
{
	for (std::pair<Entity*, ParticleComponent*> pair : listOfParticleComponents)
	{
		if (!pair.second->m_isStartInvoked)
		{
			pair.second->start();
			pair.second->m_isStartInvoked = true;
			continue;
		}
		pair.second->updateComponent();
	}
}

void ParticleSystem::render(std::vector<Entity*> entities, bool isDebugVisible)
{
	for (std::pair<Entity*, ParticleComponent*> pair : listOfParticleComponents)
	{
		pair.second->render(isDebugVisible);
	}

}

void ParticleSystem::cleanups()
{
	listOfParticleComponents.clear();
}
