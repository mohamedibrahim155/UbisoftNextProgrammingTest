#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager(SystemManager* manager) : systemManager(manager)
{
    entityCount = 0;
}

Entity* EntityManager::CreateEntity()
{
    entityCount++;
    Entity* newEntity = new Entity(entityCount);
    //newEntity->AddComponent(new Transform());
    AddEntity(newEntity);
    return  newEntity;
}

Entity* EntityManager::CreateEntityFromCopy(Entity* entity)
{
    entityCount++;
    Entity* newEntity = new Entity(*entity,entityCount);
    AddEntity(newEntity);
    return newEntity;
}

Entity* EntityManager::GetEntityByID(EntityID ID)
{
    return  entitiesMap[ID];
}

void EntityManager::AddEntity( Entity* entity)
{
    entity->manager = this;

    entitiesMap[entity->GetID()] = entity;

    systemManager->AddEntity(entity);
}

void EntityManager::RemoveEntity(EntityID ID)
{
    systemManager->RemoveEntity(ID);

    delete entitiesMap[ID];

    entitiesMap.erase(ID);

}

void EntityManager::Clean()
{
    for ( auto it = entitiesMap.begin(); it != entitiesMap.end(); )
    {
        RemoveEntity(it->first);
        it = entitiesMap.begin();
    }

    entitiesMap.clear();
}
