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
    return newEntity;
}

Entity* EntityManager::getEntityByID(EntityID ID)
{
    return  m_entitiesMap[ID];
}

void EntityManager::addEntity( Entity* entity)
{
    entity->m_entityManager = this;

    m_entitiesMap[entity->getID()] = entity;

    m_systemManager->addEntity(entity);
}

void EntityManager::removeEntity(EntityID ID)
{
    m_systemManager->removeEntity(ID);

    m_entitiesMap[ID]->Destroy(true);

    delete m_entitiesMap[ID];

    m_entitiesMap.erase(ID);

}

void EntityManager::clean()
{
    for ( auto it = m_entitiesMap.begin(); it != m_entitiesMap.end(); )
    {
        removeEntity(it->first);
        it = m_entitiesMap.begin();
    }

    m_entitiesMap.clear();
}
