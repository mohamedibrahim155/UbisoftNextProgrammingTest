#pragma once
#include "../ObjectPool.h"
#include "../src/ECS/EntityManager.h"

class EntityPool : public ObjectPool<Entity>
{
public:
	EntityPool(EntityManager* manager, Entity* prefab);
	~EntityPool() = default;

	Entity* spawnObject() override;
	void destroyObject(Entity* object) override;
	void resize() override;
	
	Entity* getEntity();
	std::vector<Entity*> getActiveEntites() const;
	void destroyAt(int index);

private:

	EntityManager* m_entityManager;
	Entity* prefabEntity;
};

