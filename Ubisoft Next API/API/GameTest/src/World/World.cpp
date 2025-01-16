#include "stdafx.h"
#include "World.h"
#include "../src/ECS/Systems/Render/RenderSystem.h"
#include "../src/ECS/Systems/CustomScripts/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/Movement/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/ECS/Systems/ParticleSystemRender/ParticleSystem.h"
#include "../src/ECS/Components/Scripts/PlayerMoveScript.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"
#include "../src/LevelManager/LevelManager.h"
#include "../src/LevelManager/Levels/Level1.h"
#include "../src/InputManager/InputManager.h"
World::World()
{
	systemManager = new SystemManager();
	entityManager = new EntityManager(systemManager);

	LevelManager::GetInstance().setManagers(systemManager, entityManager);

#pragma region Systems

	ISystem* renderSystem = new RenderSystem();
	ISystem* customScriptSystem = new CustomScriptsControllerSystem();
	ISystem* movementSystem = new MovementSystem();
	ISystem* physicsSystem = new PhysicsSystem();
	ISystem* particleSystem = new ParticleSystem();

	systemManager->registerSystem(customScriptSystem);
	systemManager->registerSystem(physicsSystem);
	systemManager->registerSystem(movementSystem);
	systemManager->registerSystem(particleSystem);
	systemManager->registerSystem(renderSystem);
#pragma endregion


	




}

void World::start()
{
	LevelManager::GetInstance().Init();
	LevelManager::GetInstance().changeScene(LEVEL_1);
//#pragma region Entities
//
//
//	std::string filename = ASSET_PATH + "IdleBLUE- 150ms - 32x32.png";
//
//	Entity* entity3 = entityManager->createEntity();
//	entity3->addComponent(new SpriteRenderer(filename, Vector2::Zero(), 3));
//
//	SpriteRenderer* sprite = (SpriteRenderer*)entity3->GetComponent(ComponentType::RENDER_COMPONENT);
//	sprite->setColor(1, 0, 0);
//	entity3->addComponent(new BoxCollider());
//	//entity3->AddComponent(new CircleCollider());
//	entity3->addComponent(new RigidBody(eBodyType::STATIC));
//	entity3->addComponent(new PlayerMoveScript());
//	entity3->transform.scale = Vector2(2, 2);
//	entity3->setTag("Sprite1");
//	entity3->transform.position = Vector2(0, -250);
//	for (size_t i = 0; i < 1; i++)
//	{
//		float randomWidth = Random::RandomRange(-(float)APP_VIRTUAL_WIDTH, (float)APP_VIRTUAL_WIDTH);
//		float randomheight = Random::RandomRange(-(float)APP_VIRTUAL_HEIGHT, (float)APP_VIRTUAL_HEIGHT);
//
//
//		Entity* entity4 = entityManager->createEntity();
//		entity4->addComponent(new SpriteSheetRenderer(filename,6,1));
//		//entity4->addComponent(new PlayerMoveScript());
//
//		SpriteRenderer* sprite2 = (SpriteRenderer*)entity4->GetComponent(ComponentType::RENDER_COMPONENT);
//
//		entity4->addComponent(new BoxCollider());
//		entity4->addComponent(new RigidBody(eBodyType::DYNAMIC));
//		//entity4->AddComponent(new CircleCollider());
//		entity4->transform.position = Vector3(randomWidth+10/2, randomheight+10/2, 0);
//		entity4->transform.scale = Vector2(1, 1);
//	}
//
//	Entity* enttity5 = entityManager-> createEntity();
//	enttity5->addComponent(new TextRenderer("Hello world"));
//	enttity5->transform.position = Vector3(0,-2,0);
//
//	Entity* buttonRender = entityManager->createEntity();
//	buttonRender->addComponent(new ButtonRenderer(ASSET_PATH + "Default\\square-rounded-512.png"));
//	buttonRender->transform.position = Vector3(0, -50, 0);
//	buttonRender->transform.scale = Vector2(0.3f,0.3f);
//
//	ButtonRenderer* button = dynamic_cast<ButtonRenderer*>(buttonRender->GetComponent(ComponentType::RENDER_COMPONENT));
//
//	button->addListenersOnButtonPress([this]()
//		{ 
//				Entity* firstEntity = entityManager->createEntity();
//
//				float randomWidth = Random::RandomRange(-(float)APP_VIRTUAL_WIDTH, (float)APP_VIRTUAL_WIDTH);
//				float randomheight = Random::RandomRange(-(float)APP_VIRTUAL_HEIGHT, (float)APP_VIRTUAL_HEIGHT);
//				firstEntity->addComponent(new SpriteSheetRenderer(ASSET_PATH + "IdleBLUE- 150ms - 32x32.png", 6, 1));
//				//firstEntity->addComponent(new PlayerMoveScript());
//				firstEntity->addComponent(new RigidBody(eBodyType::DYNAMIC));
//				firstEntity->addComponent(new CircleCollider());
//				firstEntity->transform.position = Vector3(randomWidth / 2, randomWidth / 2, 0);
//
//
//
//			});
//
//	button->addListenersOnButtonHover([this]()
//			{
//				Entity* entity3 = entityManager->getEntityByID(1);
//
//				SpriteRenderer* spriteEn2 = (SpriteRenderer*)entity3->GetComponent(ComponentType::RENDER_COMPONENT);
//
//				spriteEn2->setColor(0, 1, 1);
//			});
//
//	button->addListenersOnButtonHoverExit([this]()
//		{
//			Entity* firstEntity3 = entityManager->getEntityByID(1);
//
//			SpriteRenderer* spriteEn3 = (SpriteRenderer*)firstEntity3->GetComponent(ComponentType::RENDER_COMPONENT);
//
//			spriteEn3->setColor(1, 1, 1);
//		});
//
//#pragma endregion

#pragma region SystemStart
//	systemManager->start();
#pragma endregion
}

void World::update(float deltaTime)
{
	if (InputManager::GetInstance().GetKeyDown('V'))
	{
		bool debug = systemManager->IsDebug();

		systemManager->setDebugVisible(!debug);
	}
	systemManager->updateSystems(deltaTime);
}

void World::render()
{
	systemManager->render();
}

void World::clean()
{
	LevelManager::GetInstance().cleanScene();
	
}
