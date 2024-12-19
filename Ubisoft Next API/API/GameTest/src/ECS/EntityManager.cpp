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
    newEntity->AddComponent(new Transform());
    AddEntity(newEntity);
    return  newEntity;
}

Entity* EntityManager::GetEntityByID(EntityID ID)
{
    return  entitiesMap[entityCount];
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

    entityCount = (entityCount < 0) ? 0 : --entityCount;
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
