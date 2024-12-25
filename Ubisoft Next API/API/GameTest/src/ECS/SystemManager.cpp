#include "stdafx.h"
#include "SystemManager.h"

void SystemManager::RegisterSystem(ISystem* system)
{
    system->systemManager = this;
    systemsMap[system->systemType] = system;
}

void SystemManager::RemoveSystem(ISystem* system)
{
    systemsMap.erase(system->systemType);
}

void SystemManager::AddEntity(Entity* entity)
{
    entitiesMap[entity->GetID()] =  entity;

    listOfEntities.push_back(entity);
}

void SystemManager::RemoveEntity(EntityID ID)
{
    entitiesMap.erase(ID);
}

void SystemManager::CleanSystem()
{
    for (std::pair<eSystemType, ISystem*> system : systemsMap)
    {
        system.second->Cleanups();

        delete  system.second;
    }

    systemsMap.clear();
    entitiesMap.clear();
    listOfEntities.clear();
}

ISystem* SystemManager::GetSystem(eSystemType type)
{
    return systemsMap[type];
}

std::vector<Entity*> SystemManager::GetEntities() const
{
    return listOfEntities;
}

void SystemManager::Start()
{
    for (std::pair<eSystemType, ISystem*> system : systemsMap)
    {
        system.second->Start(listOfEntities);
    }
}

void SystemManager::UpdateSystems(float deltaTime)
{
    for (std::pair<eSystemType, ISystem*> system: systemsMap)
    {
        system.second->Update(listOfEntities, deltaTime);
    }
}

void SystemManager::Render()
{
    for (std::pair<eSystemType, ISystem*> system : systemsMap)
    {
        system.second->Render(listOfEntities);
    }
}
