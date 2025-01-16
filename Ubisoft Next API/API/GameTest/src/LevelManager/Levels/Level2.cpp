#include "stdafx.h"
#include "Level2.h"
#include "../src/ECS/Systems/RenderSystem.h"
#include "../src/ECS/Systems/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/ECS/Components/Scripts/PlayerMoveScript.h"
#include "../src/ECS/Components/Scripts/PoolTestingScript.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"

void Level2::initialize()
{


	std::string filename = ASSET_PATH + "IdleBLUE- 150ms - 32x32.png";


	Entity* entity3 = entityManager->createEntity();
	entity3->addComponent(new SpriteRenderer(filename, Vector2::Zero(), 3));
	entity3->addComponent(new PlayerMoveScript());
	entity3->transform.scale = Vector2(2, 2);
	entity3->setTag("Sprite1");
	//entity3->transform.position = Vector2(0, 0);


	Entity* entityWithPool = entityManager->createEntity();
	entityWithPool->setTag("PoolManager");
	entityWithPool->addComponent(new PoolTestingScript(entityManager));



}

void Level2::cleanScene()
{
	systemManager->cleanSystem();
}
