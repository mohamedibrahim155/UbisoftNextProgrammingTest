#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager(SystemManager* manager) : systemManager(manager)
{
    entityCount = 0;
}

Entity* EntityManager::createEntity()
{
    entityCount++;
    Entity* newEntity = new Entity(entityCount);
    //newEntity->AddComponent(new Transform());
    addEntity(newEntity);
    return  newEntity;
}

Entity* EntityManager::createEntityFromCopy(Entity* entity)
{
    entityCount++;
    Entity* newEntity = new Entity(*entity,entityCount);
    addEntity(newEntity);
    return newEntity;
}

Entity* EntityManager::getEntityByID(EntityID ID)
{
    return  entitiesMap[ID];
}

void EntityManager::addEntity( Entity* entity)
{
    entity->manager = this;

    entitiesMap[entity->getID()] = entity;

    systemManager->addEntity(entity);
}

void EntityManager::removeEntity(EntityID ID)
{
    systemManager->removeEntity(ID);

    delete entitiesMap[ID];

    entitiesMap.erase(ID);

}

void EntityManager::clean()
{
    for ( auto it = entitiesMap.begin(); it != entitiesMap.end(); )
    {
        removeEntity(it->first);
        it = entitiesMap.begin();
    }

    entitiesMap.clear();
}
