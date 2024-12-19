#include "stdafx.h"
#include "SystemManager.h"

void SystemManager::RegisterSystem(ISystem* system)
{
    system->systemManager = this;
	systemsMap[systemCount] = system;
	systemCount++;
}

void SystemManager::RemoveSystem(ISystem* system)
{
    // TODO: Check if the system removing properly and ordered well
    for (auto it = systemsMap.begin(); it != systemsMap.end(); ++it)
    {
        if (it->second == system)
        {
            int removeKey = it->first;
            int lastIndex = systemsMap.size() - 1;

            if (removeKey != lastIndex)
            {
                systemsMap[removeKey] = systemsMap[lastIndex];; // replacing last to removed index
            }

            systemsMap.erase(lastIndex);
            systemCount--;
            return;
        }
    }
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
    for (std::pair<int, ISystem*> system : systemsMap)
    {
        system.second->Cleanups();

        delete  system.second;
    }

    systemsMap.clear();
    entitiesMap.clear();
    listOfEntities.clear();
}

void SystemManager::Start()
{
    for (std::pair<int, ISystem*> system : systemsMap)
    {
        system.second->Start(listOfEntities);
    }
}

void SystemManager::UpdateSystems(float deltaTime)
{
    for (std::pair<int, ISystem*> system: systemsMap)
    {
        system.second->Update(listOfEntities, deltaTime);
    }
}

void SystemManager::Render()
{
    for (std::pair<int, ISystem*> system : systemsMap)
    {
        system.second->Render(listOfEntities);
    }
}
