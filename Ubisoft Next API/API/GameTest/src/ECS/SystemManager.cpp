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
    Entity* entity = m_entitiesMap[ID];

    OnEntityRemoved.Invoke(entity);

    m_listOfEntities.erase(std::remove(m_listOfEntities.begin(), m_listOfEntities.end(), entity));

    m_entitiesMap.erase(ID);
}





ISystem* SystemManager::getSystem(eSystemType type)
{
    return m_systemsMap[type];
}

void SystemManager::SetDebugVisible(bool isVisible)
{
    m_debugVisible = isVisible;
}


bool SystemManager::IsDebug() const
{
    return m_debugVisible;
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
        system.second->render(m_listOfEntities, m_debugVisible);
    }
}

void SystemManager::cleanups()
{
    clearEntities();
    clearSystems();

    m_systemsMap.clear();
}

void SystemManager::cleanSystem()
{
    clearEntities();
    clearSystems(false);
}

void SystemManager::clearSystems(bool canDelete)
{
    for (std::pair<eSystemType, ISystem*> system : m_systemsMap)
    {
        system.second->cleanups();

        if (canDelete)
        {
            delete  system.second;
        }
    }
}

void SystemManager::clearEntities()
{

    if (m_entitiesMap.size() > 0)
    {
        for (auto it = m_entitiesMap.begin(); it != m_entitiesMap.end(); )
        {
            EntityID Id = it->first;
            Entity* entity = it->second;

            removeEntity(Id);

            delete entity;
            it = m_entitiesMap.begin();
        }
    }

    m_entitiesMap.clear();

    OnEntityAdded.clear();
    OnEntityRemoved.clear();

    m_listOfEntities.clear();
}
