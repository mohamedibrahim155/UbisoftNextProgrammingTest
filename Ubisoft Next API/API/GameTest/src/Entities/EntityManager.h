#pragma once
#include "Entity.h"
#include <unordered_map>

class CEntityManager
{
public:

	static CEntityManager& GetInstance();
	void AddEntity(CEntity* entity);
	void AddEntity(std::string m_entityID,CEntity* entity);
	void RemoveEntity(std::string m_entityID);
	void RemoveEntity(CEntity* entity);


	void Start();
	void Update();
	void Clean();
	void Render();
	void DestroyEntity(CEntity* entity);


private:

	int entitiesCount = 0;

	std::unordered_map<std::string, CEntity*> m_listOfEntities;
	std::vector<std::string> destroyedEntities;

	std::unordered_map<std::string, CEntity*>::iterator iterator;
};
