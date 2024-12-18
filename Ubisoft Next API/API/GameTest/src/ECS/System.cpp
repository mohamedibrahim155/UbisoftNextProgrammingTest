#include "stdafx.h"
#include "System.h"

void ISystem::RemoveEntity(Entity* entity)
{
    std::unordered_map<Entity*,IComponent*>::iterator it = listOfRenderers.find(entity);

    if (it != listOfRenderers.end())
    {
        listOfRenderers.erase(it);
    }
}

void ISystem::AddEntity(Entity* entity, IComponent* component)
{
    listOfRenderers[entity] = component;
}
