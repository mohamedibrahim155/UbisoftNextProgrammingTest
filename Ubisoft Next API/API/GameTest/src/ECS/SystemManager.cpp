#include "stdafx.h"
#include "SystemManager.h"

void SystemManager::registerSystem(ISystem* system)
{
    system->systemManager = this;
    systemsMap[system->systemType] = system;
}

void SystemManager::removeSystem(ISystem* system)
{
    systemsMap.erase(system->systemType);
}

void SystemManager::addEntity(Entity* entity)
{
    entitiesMap[entity->getID()] =  entity;

    listOfEntities.push_back(entity);

    OnEntityAdded.Invoke(entity);
}

void SystemManager::removeEntity(EntityID ID)
{
    OnEntityRemoved.Invoke(entitiesMap[ID]);

    entitiesMap.erase(ID);
}

void SystemManager::cleanSystem()
{
    for (std::pair<eSystemType, ISystem*> system : systemsMap)
    {
        system.second->cleanups();

        delete  system.second;
    }

    systemsMap.clear();
    entitiesMap.clear();
    listOfEntities.clear();
    OnEntityAdded.clear();
    OnEntityRemoved.clear();
}

ISystem* SystemManager::getSystem(eSystemType type)
{
    return systemsMap[type];
}

Entity* SystemManager::getEntityByID(EntityID ID)
{
    return entitiesMap[ID];
}

std::vector<Entity*> SystemManager::getEntities() const
{
    return listOfEntities;
}

void SystemManager::start()
{
    for (std::pair<eSystemType, ISystem*> system : systemsMap)
    {
        system.second->start(listOfEntities);
    }
}

void SystemManager::updateSystems(float deltaTime)
{
    for (std::pair<eSystemType, ISystem*> system: systemsMap)
    {
        system.second->update(listOfEntities, deltaTime);
    }
}

void SystemManager::render()
{
    for (std::pair<eSystemType, ISystem*> system : systemsMap)
    {
        system.second->render(listOfEntities);
    }
}
