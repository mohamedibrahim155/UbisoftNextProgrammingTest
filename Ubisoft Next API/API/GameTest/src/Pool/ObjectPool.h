#pragma once
#include <vector>
#include "../src/ECS/Entity.h"
#include <queue>

template<typename T>
class ObjectPool
{
public:

	virtual ~ObjectPool() {};
	virtual T* spawnObject() = 0;
	virtual void resize() = 0;

	virtual void cleanup()
	{
		for (T* obj : m_listOfPools)
		{
			delete obj;
		}
		m_listOfPools.clear();
	}

	virtual void destroyObject(T* object) = 0;

protected:

	int m_resizeAmount = 10;
	std::vector<T*> m_listOfPools;
};

