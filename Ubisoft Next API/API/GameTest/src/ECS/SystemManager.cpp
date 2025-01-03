#include "stdafx.h"
#include "SystemManager.h"

void SystemManager::registerSystem(ISystem* system)
{
    system->m_systemManager = this;
    m_systemsMap[system->m_systemType] = system;
}

void SystemManager::removeSystem(ISystem* system)
{
    m_systemsMap.erase(system->m_systemType);
}

void SystemManager::addEntity(Entity* entity)
{
    m_entitiesMap[entity->getID()] =  entity;

    m_listOfEntities.push_back(entity);

    OnEntityAdded.Invoke(entity);
}

void SystemManager::removeEntity(EntityID ID)
{
    OnEntityRemoved.Invoke(m_entitiesMap[ID]);

    m_listOfEntities.erase(std::remove(m_listOfEntities.begin(), m_listOfEntities.end(), m_entitiesMap[ID]));

    m_entitiesMap.erase(ID);
}

void SystemManager::cleanSystem()
{
    for (std::pair<eSystemType, ISystem*> system : m_systemsMap)
    {
        system.second->cleanups();

        delete  system.second;
    }

    m_systemsMap.clear();
    m_entitiesMap.clear();
    m_listOfEntities.clear();

   // cleanEvents();

    OnEntityAdded.clear();
    OnEntityRemoved.clear();
}

void SystemManager::cleanEvents()
{
    OnEntityAdded.clear();
    OnEntityRemoved.clear();
}



ISystem* SystemManager::getSystem(eSystemType type)
{
    return m_systemsMap[type];
}


Entity* SystemManager::getEntityByID(EntityID ID)
{
    return m_entitiesMap[ID];
}

std::vector<Entity*> SystemManager::getEntities() const
{
    return m_listOfEntities;
}

void SystemManager::start()
{
    for (std::pair<eSystemType, ISystem*> system : m_systemsMap)
    {
        system.second->start(m_listOfEntities);
    }
}

void SystemManager::updateSystems(float deltaTime)
{

    for (const std::pair<eSystemType, ISystem*>& system: m_systemsMap)
    {
        system.second->update(m_listOfEntities, deltaTime);
    }
}

void SystemManager::render()
{
    for (std::pair<eSystemType, ISystem*> system : m_systemsMap)
    {
        system.second->render(m_listOfEntities);
    }
}
