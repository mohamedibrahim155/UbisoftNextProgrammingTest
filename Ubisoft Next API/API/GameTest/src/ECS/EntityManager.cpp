#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager(SystemManager* manager) : systemManager(manager)
{
}

Entity* EntityManager::CreateEntity()
{
    entityCount++;
    Entity* newEntity = new Entity(entityCount);
    newEntity->manager = this;
    newEntity->AddComponent(new Transform());
    entitiesMap[entityCount] = newEntity;
    systemManager->AddEntity(newEntity);
    return  newEntity;
}

Entity* EntityManager::GetEntityByID(EntityID ID)
{
    return  entitiesMap[entityCount];
}

void EntityManager::DestroyEntity(EntityID ID)
{
    Entity* entity = GetEntityByID(ID);
    systemManager->RemoveEntity(ID);
    entitiesMap.erase(ID);
}

void EntityManager::Clean()
{
    for (auto it = entitiesMap.begin(); it != entitiesMap.end(); )
    {
        DestroyEntity(it->first);
        it = entitiesMap.begin();
    }
    entitiesMap.clear();
    systemManager->CleanSystem();
    
}

void EntityManager::SetSystemManager(SystemManager* manager)
{
    this->systemManager = systemManager;
}
