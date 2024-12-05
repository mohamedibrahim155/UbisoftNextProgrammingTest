#include "Entity.h"
#include "stdafx.h"
CEntity::CEntity()
{
	CEntityManager::GetInstance().AddEntity(this);
}

CEntity::~CEntity()
{
	CEntityManager::GetInstance().RemoveEntity(this);
}


void CEntity::Destroy()
{
	OnDestroyedEvent.Invoke();
	OnDestroy();
}

void CEntity::CopyFromOther(CEntity* entity)
{
	this->m_entityID = entity->m_entityID;
	this->m_isEnabled = entity->m_isEnabled;
}

void CEntity::InitializeEntity(CEntity* entity)
{
	CEntityManager::GetInstance().AddEntity(entity);
}

