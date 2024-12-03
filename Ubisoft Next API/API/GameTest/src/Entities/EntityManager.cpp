#include "EntityManager.h"
#include "stdafx.h"


CEntityManager& CEntityManager::GetInstance()
{
	static CEntityManager instance;
	return instance;
}

void CEntityManager::AddEntity(CEntity* entity)
{
	std::string m_entityID =  std::to_string((int)m_listOfEntities.size());
	entity->m_entityID = m_entityID;

	m_listOfEntities[m_entityID] = entity;
}

void CEntityManager::AddEntity(std::string m_entityID, CEntity* entity)
{
	entity->m_entityID = m_entityID;

	m_listOfEntities[m_entityID] = entity;
}

void CEntityManager::RemoveEntity(std::string m_entityID)
{
	iterator = m_listOfEntities.begin();
	for (iterator = m_listOfEntities.begin(); iterator != m_listOfEntities.end(); iterator++)
	{
		if (iterator->first == m_entityID)
		{
			DestroyEntity(iterator->second);

			destroyedEntities.push_back(m_entityID);
			return;
		}
	}

}

void CEntityManager::RemoveEntity(CEntity* entity)
{
	iterator = m_listOfEntities.begin();
	for (iterator = m_listOfEntities.begin(); iterator != m_listOfEntities.end(); iterator++)
	{
		if (iterator->second == entity)
		{
			DestroyEntity(iterator->second);

			destroyedEntities.push_back(iterator->first);
			return;
		}
	}
}




void CEntityManager::Start()
{
	for (std::pair<const std::string, CEntity*>item : m_listOfEntities)
	{
		item.second->Start();
	}
}

void CEntityManager::Update()
{
	for (const std::string& id : destroyedEntities)
	{
		m_listOfEntities[id] = nullptr;
		delete m_listOfEntities[id];

		m_listOfEntities.erase(id);
	}

	destroyedEntities.clear();

	try
	{
		for (std::pair<const std::string&, CEntity*> item : m_listOfEntities)
		{
			item.second->Update();
		}
	}
	catch (const std::exception& e)
	{
		//std::cout << e.what() << std::endl;
	}
}

void CEntityManager::Clean()
{
	while (m_listOfEntities.size() != 0)
	{
		m_listOfEntities.begin()->second->Clean();

		m_listOfEntities.begin()->second = nullptr;

		delete m_listOfEntities.begin()->second;

		m_listOfEntities.erase(m_listOfEntities.begin());
	}

	m_listOfEntities.clear();
}

void CEntityManager::Render()
{
	for (std::string& id : destroyedEntities)
	{
		m_listOfEntities[id] = nullptr;
		delete m_listOfEntities[id];

		m_listOfEntities.erase(id);
	}

	try
	{

		for (std::pair<const std::string&, CEntity*> item : m_listOfEntities)
		{
			item.second->Render();
		}
	}
	catch (const std::exception& e)
	{
	//	std::cout << e.what() << std::endl;
	}
}

void CEntityManager::DestroyEntity(CEntity* entity)
{
	entity->OnDestroy();
}
