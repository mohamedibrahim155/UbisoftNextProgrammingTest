#include "stdafx.h"
#include "SystemManager.h"

void SystemManager::RegisterSystem(ISystem* system)
{
	listOfSystems[systemCount] = system;
	systemCount++;


}

void SystemManager::RemoveSystem(ISystem* system)
{
    // TODO: Check if the system removing properly and ordered well
    for (auto it = listOfSystems.begin(); it != listOfSystems.end(); ++it)
    {
        if (it->second == system)
        {
            int removeKey = it->first;
            int lastIndex = listOfSystems.size() - 1;

            if (removeKey != lastIndex)
            {
                listOfSystems[removeKey] = listOfSystems[lastIndex];; // replacing last to removed index
            }

            listOfSystems.erase(lastIndex);
            systemCount--;
            return;
        }
    }
}

void SystemManager::AddEntity(Entity* entity)
{
    listOfEntites.push_back(entity);
}

void SystemManager::RemoveEntity(Entity* entity)
{
    std::vector<Entity*>::iterator it = std::find(listOfEntites.begin(), listOfEntites.end(), entity);

    if (it != listOfEntites.end())
    {
        listOfEntites.erase(it);
    }
}

void SystemManager::CleanSystem()
{
    for (std::pair<int, ISystem*> system : listOfSystems)
    {
        system.second->Cleanups();

        delete  system.second;
    }

    listOfSystems.clear();


    for (Entity* entity:  listOfEntites)
    {
        entity->CleanUps();
    }

    listOfEntites.clear();
}

void SystemManager::Start()
{
    for (std::pair<int, ISystem*> system : listOfSystems)
    {
        system.second->Start();
    }
}

void SystemManager::UpdateSystems(float deltaTime)
{
    for (std::pair<int, ISystem*> system: listOfSystems)
    {
        system.second->Update(listOfEntites, deltaTime);
    }
}

void SystemManager::Render()
{
    for (std::pair<int, ISystem*> system : listOfSystems)
    {
        system.second->Render(listOfEntites);
    }
}
