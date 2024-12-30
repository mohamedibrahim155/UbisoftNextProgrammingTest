#include "stdafx.h"
#include "World.h"
#include "../src/ECS/Systems/RenderSystem.h"
#include "../src/ECS/Systems/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/ECS/Components/Scripts/PlayerMoveScript.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"
World::World()
{
	systemManager = new SystemManager();
	entityManager = new EntityManager(systemManager);


#pragma region Systems

	ISystem* renderSystem = new RenderSystem();
	ISystem* customScriptSystem = new CustomScriptsControllerSystem();
	ISystem* movementSystem = new MovementSystem();
	ISystem* physicsSystem = new PhysicsSystem();

	systemManager->registerSystem(customScriptSystem);
	systemManager->registerSystem(physicsSystem);
	systemManager->registerSystem(movementSystem);
	systemManager->registerSystem(renderSystem);
#pragma endregion







}

void World::start()
{
#pragma region Entities


	std::string filename = ASSET_PATH + "IdleBLUE- 150ms - 32x32.png";

	Entity* entity3 = entityManager->createEntity();
	entity3->addComponent(new SpriteRenderer(filename, Vector2::Zero(), 3));

	SpriteRenderer* sprite = (SpriteRenderer*)entity3->GetComponent(ComponentType::RENDER_COMPONENT);
	sprite->setColor(1, 0, 0);
	entity3->addComponent(new BoxCollider());
	//entity3->AddComponent(new CircleCollider());
	entity3->addComponent(new RigidBody(eBodyType::STATIC));
	//entity3->AddComponent(new PlayerMoveScript());
	entity3->transform.scale = Vector2(2, 1);
	entity3->transform.position = Vector2(0, -250);
	for (size_t i = 0; i < 10; i++)
	{
		float randomWidth = Random::RandomRange(-(float)APP_VIRTUAL_WIDTH, (float)APP_VIRTUAL_WIDTH);
		float randomheight = Random::RandomRange(-(float)APP_VIRTUAL_HEIGHT, (float)APP_VIRTUAL_HEIGHT);


		Entity* entity4 = entityManager->createEntity();
		entity4->addComponent(new SpriteSheetRenderer(filename,6,1));
		entity4->addComponent(new PlayerMoveScript());

		SpriteRenderer* sprite2 = (SpriteRenderer*)entity4->GetComponent(ComponentType::RENDER_COMPONENT);

		entity4->addComponent(new BoxCollider());
		entity4->addComponent(new RigidBody(eBodyType::DYNAMIC));
		//entity4->AddComponent(new CircleCollider());
		entity4->transform.position = Vector3(randomWidth+10/2, randomheight+10/2, 0);
		entity4->transform.scale = Vector2(1, 1);
	}

	Entity* enttity5 = entityManager-> createEntity();
	enttity5->addComponent(new TextRenderer("Hello world"));
	enttity5->transform.position = Vector3(0,-2,0);

	Entity* buttonRender = entityManager->createEntity();
	buttonRender->addComponent(new ButtonRenderer(ASSET_PATH + "Default\\square-rounded-512.png"));
	buttonRender->transform.position = Vector3(0, -50, 0);
	buttonRender->transform.scale = Vector2(0.3f,0.3f);

	ButtonRenderer* button = dynamic_cast<ButtonRenderer*>(buttonRender->GetComponent(ComponentType::RENDER_COMPONENT));

	button->addListenersOnButtonPress([&]()
		{ 
				Entity* firstEntity = entityManager->getEntityByID(1);

				SpriteRenderer* spriteEn = (SpriteRenderer*)firstEntity->GetComponent(ComponentType::RENDER_COMPONENT);

				spriteEn->setColor(1, 0.5f, 0);
			});

	button->addListenersOnButtonHover([&]()
			{
				Entity* firstEntity2 = entityManager->getEntityByID(1);

				SpriteRenderer* spriteEn2 = (SpriteRenderer*)firstEntity2->GetComponent(ComponentType::RENDER_COMPONENT);

				spriteEn2->setColor(0, 0, 1);
			});

	button->addListenersOnButtonHoverExit([&]()
		{
			Entity* firstEntity3 = entityManager->getEntityByID(1);

			SpriteRenderer* spriteEn3 = (SpriteRenderer*)firstEntity3->GetComponent(ComponentType::RENDER_COMPONENT);

			spriteEn3->setColor(1, 1, 1);
		});

#pragma endregion

#pragma region SystemStart
	systemManager->start();
#pragma endregion
}

void World::update(float deltaTime)
{
	systemManager->updateSystems(deltaTime);
}

void World::render()
{
	systemManager->render();
}

void World::clean()
{
	entityManager->clean();
	systemManager->cleanSystem();

	delete systemManager;
	delete entityManager;
}
