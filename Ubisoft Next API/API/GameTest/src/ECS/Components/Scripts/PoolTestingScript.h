#pragma once
#include "ScriptComponent.h"
#include "../src/Pool/Entity/EntityPool.h"
class PoolTestingScript : public BaseScriptComponent
{
public:
	PoolTestingScript(EntityManager* entityManager);
	~PoolTestingScript() override;

	 void start()  override;
	 void updateComponent() override;
	 void render(bool isDebugVisible)override {} ;
	 void cleanUp() override;

    PoolTestingScript* clone() const override
	{
		return new PoolTestingScript(this->m_entityManager);
	};

public :

	EntityPool* m_entitiesPool;
	Entity* prefab;
	EntityManager* m_entityManager;

	Entity* pooledGameObject;

	void Enable();
	void DisableCurrent();

	std::unordered_map<int, bool> keys;

	bool IsKeyPressedOnce(int key);
};

