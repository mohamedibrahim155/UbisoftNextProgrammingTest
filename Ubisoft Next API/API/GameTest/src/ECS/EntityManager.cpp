#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager(SystemManager* manager) : systemManager(manager)
{
}

Entity* EntityManager::CreateEntity()
{
    entityCount++;
    Entity* newEntity = new Entity(entityCount);
    newEntity->AddComponent(new Transform());
    listOfEntites[entityCount] = newEntity;
    systemManager->AddEntity(newEntity);
    return  newEntity;
}

Entity* EntityManager::GetEntityByID(int ID)
{
    return  listOfEntites[entityCount];
}

void EntityManager::DestroyEntity(int ID)
{
    Entity* entity = GetEntityByID(ID);

    entity->Destroy();

    listOfEntites.erase(ID);

}

void EntityManager::Clean()
{
    std::unordered_map<int, Entity*> ::iterator it;
    for (it  = listOfEntites.begin(); it != listOfEntites.end() ; ++it)
    {
        it->second->Destroy();
        delete it->second;
    }

    listOfEntites.clear();
}

void EntityManager::SetSystemManager(SystemManager* manager)
{
    this->systemManager = systemManager;
}
