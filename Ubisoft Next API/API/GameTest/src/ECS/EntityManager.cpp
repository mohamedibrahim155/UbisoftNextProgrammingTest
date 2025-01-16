#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager(SystemManager* manager) : m_systemManager(manager)
{
    m_entityID = 0;
}

Entity* EntityManager::createEntity()
{
    m_entityID++;

    Entity* newEntity = new Entity(m_entityID);
    addEntity(newEntity);
    return  newEntity;
}

Entity* EntityManager::createEntityFromCopy(Entity* entity)
{
    m_entityID++;

    Entity* newEntity = new Entity(*entity,m_entityID);
    addEntity(newEntity);
    newEntity->copyComponents(*entity);
    return newEntity;
}


void EntityManager::addEntity( Entity* entity)
{
    m_systemManager->addEntityToSystem(entity);

    subscribeOnDestroy(entity);
}

void EntityManager::subscribeOnDestroy(Entity* entity)
{
    entity->OnDestroyed.Subscribe([this, entity]()
        {
            destroyEntity(entity);
        });
}

void EntityManager::removeEntity(EntityID ID)
{
        m_systemManager->removeEntity(ID);
}

void EntityManager::clean()
{
    m_entityID = 0;
}

void EntityManager::destroyEntity(Entity* entity)
{
    entity->Destroy();

    removeEntity(entity->getID());

    delete entity;
}


