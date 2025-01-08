#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager(SystemManager* manager) : m_systemManager(manager)
{
    m_entityCount = 0;
}

Entity* EntityManager::createEntity()
{
    m_entityCount++;
    Entity* newEntity = new Entity(m_entityCount);
    addEntity(newEntity);
    return  newEntity;
}

Entity* EntityManager::createEntityFromCopy(Entity* entity)
{
    m_entityCount++;
    Entity* newEntity = new Entity(*entity,m_entityCount);
    addEntity(newEntity);
    newEntity->copyComponents(*entity);
    return newEntity;
}


void EntityManager::addEntity( Entity* entity)
{

    m_systemManager->addEntity(entity);

    HandleOnDestroyed(entity);
}

void EntityManager::HandleOnDestroyed(Entity* entity)
{
    entity->OnDestroyed.Subscribe([this, entity]()
        {
            DestroyEntity(entity);
        });
}

void EntityManager::removeEntity(EntityID ID)
{
        m_systemManager->removeEntity(ID);
}

void EntityManager::clean()
{
    m_entityCount = 0;
}

void EntityManager::DestroyEntity(Entity* entity)
{
    entity->Destroy();

    removeEntity(entity->getID());

    delete entity;
}


