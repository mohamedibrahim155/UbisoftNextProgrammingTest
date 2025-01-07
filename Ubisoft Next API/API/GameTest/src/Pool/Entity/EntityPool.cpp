#include "stdafx.h"
#include "EntityPool.h"

EntityPool::EntityPool(EntityManager* entitymanager, Entity* prefab) : ObjectPool(), m_entityManager(entitymanager)
{
	prefabEntity = prefab;

	resize();
}

Entity* EntityPool::spawnObject()
{
	Entity* entity = m_entityManager->createEntityFromCopy(prefabEntity);
	entity->setActive(false);
	return entity;
}

Entity* EntityPool::getEntity()
{
	for (Entity* entity : m_listOfPools)
	{
		if (!entity->IsActive())
		{
			entity->setActive(true);

			return entity;
		}
	}

	int listSize = m_listOfPools.size();

	resize();

	return m_listOfPools[listSize];
}

std::vector<Entity*> EntityPool::getActiveEntites() const
{
	std::vector<Entity*> listOfActives;

	for (Entity* entity : m_listOfPools)
	{
		if (entity->IsActive())
		{
			listOfActives.push_back(entity);
		}
	}

	return listOfActives;
}

void EntityPool::resize()
{
	
	int prevSize = m_listOfPools.size();

	m_listOfPools.resize(m_listOfPools.size() + m_resizeAmount);

	for (size_t i = prevSize; i < m_listOfPools.size(); i++)
	{
		m_listOfPools[i] = spawnObject();
	}
}



void EntityPool::destroyObject(Entity* object)
{
	if (object->IsActive())
	{
		object->setActive(false);
	}
	
}

void EntityPool::destroyAt(int index)
{
	if (index < m_listOfPools.size())
	{
		destroyObject(m_listOfPools[index]);
	}
}


