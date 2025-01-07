#include "stdafx.h"
#include "PoolTestingScript.h"
#include"../src/ECS/Components/Collider/BoxCollider.h"
#include"../src/ECS/Components/Rigidbody/Rigidbody.h"
PoolTestingScript::PoolTestingScript() : BaseScriptComponent()
{
	//prefab = nullptr;
	m_entitiesPool = nullptr;
}

PoolTestingScript::~PoolTestingScript()
{
}

void PoolTestingScript::start()
{
	std::string filename = ASSET_PATH + "IdleBLUE- 150ms - 32x32.png";
	m_entityManager = getEntity()->m_entityManager;


	prefab = m_entityManager->createEntity();
	prefab->setTag("blueSprte");
	prefab->addComponent(new SpriteRenderer(filename, Vector2::Zero(), 3));
	prefab->addComponent(new BoxCollider());
	prefab->addComponent(new RigidBody(eBodyType::DYNAMIC));
	prefab->transform.position = Vector2::Zero();
	prefab->setActive(false);

	m_entitiesPool = new EntityPool(m_entityManager, prefab);

	

}

void PoolTestingScript::updateComponent()
{
	if (IsKeyPressedOnce('T'))
	{
		//On Enable

		Enable();
	}

	if (IsKeyPressedOnce('E'))
	{
		//On Disable

	
		DisableCurrent();
	}

}

void PoolTestingScript::Enable()
{
	pooledGameObject = m_entitiesPool->getEntity();

	if (pooledGameObject)
	{
		float randomWidth = Random::RandomRange(-(float)APP_VIRTUAL_WIDTH , (float)APP_VIRTUAL_WIDTH );
		float randomheight = Random::RandomRange(-(float)APP_VIRTUAL_HEIGHT , (float)APP_VIRTUAL_HEIGHT);

		pooledGameObject->transform.position = Vector2(0, -50);
		pooledGameObject->transform.scale = Vector2(1, 1);

	}
}

void PoolTestingScript::DisableCurrent()
{
	std::vector<Entity*> activeList = m_entitiesPool->getActiveEntites();
	for (Entity* entity : activeList)
	{
		if (entity)
		{
			m_entitiesPool->destroyObject(entity);

			return;
		}
	}
	
}

bool PoolTestingScript::IsKeyPressedOnce(int key)
{
	bool isPressed = App::IsKeyPressed(key);


	bool wasPressed = keys[key];
	keys[key] = isPressed;

	return isPressed && !wasPressed;
}
