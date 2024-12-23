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

	systemManager->RegisterSystem(customScriptSystem);
	systemManager->RegisterSystem(physicsSystem);
	systemManager->RegisterSystem(movementSystem);
	systemManager->RegisterSystem(renderSystem);
#pragma endregion







}

void World::Start()
{
#pragma region Entities


	std::string filename = ASSET_PATH + "IdleBLUE- 150ms - 32x32.png";

	for (size_t i = 0; i < 1; i++)
	{
		float randomWidth = Random::RandomRange(-(float)APP_VIRTUAL_WIDTH, (float)APP_VIRTUAL_WIDTH);
		float randomheight = Random::RandomRange(-(float)APP_VIRTUAL_HEIGHT, (float)APP_VIRTUAL_HEIGHT);
		/*Entity* entity1 = entityManager->CreateEntity();
		entity1->AddComponent(new SpriteRenderer(filename, Vector2::Zero()));
		entity1->AddComponent(new PlayerMoveScript());
		entity1->transform.position = Vector3(0, 0, 0);

		Entity* entity2 = entityManager->CreateEntity();
		entity2->AddComponent(new SpriteRenderer(filename, Vector2::Zero(),5));

		randomWidth = Random::RandomRange(-(float)(APP_VIRTUAL_WIDTH / 2), (float)(APP_VIRTUAL_WIDTH / 2));
		randomheight = Random::RandomRange(-(float)(APP_VIRTUAL_HEIGHT / 2), (float)(APP_VIRTUAL_HEIGHT / 2));
		entity2->transform.position = Vector3(0, 0, 0);

		Entity* entity3 = entityManager->CreateEntity();
		entity3->AddComponent(new SpriteRenderer(filename, Vector2::Zero(),3));
		((SpriteRenderer*)entity3->GetComponent(ComponentType::RENDER_COMPONENT))->SetColor(Vector3(1,0,0));
		entity3->transform.scale = Vector2(5, 5);*/



		Entity* entity3 = entityManager->CreateEntity();
		entity3->AddComponent(new SpriteRenderer(filename, Vector2::Zero(), 3));

		SpriteRenderer* sprite = (SpriteRenderer*)entity3->GetComponent(ComponentType::RENDER_COMPONENT);
		sprite->SetColor(1, 0, 0);
		entity3->AddComponent(new BoxCollider());
		entity3->AddComponent(new CircleCollider());
		entity3->AddComponent(new RigidBody(eBodyType::STATIC));
		//entity3->AddComponent(new PlayerMoveScript());
		entity3->transform.scale = Vector2(2, 2); 
	//	entity3->transform.position = Vector2(0, 0); 


		//Entity* entity4 = entityManager->CreateEntity();
		//entity4->AddComponent(new SpriteSheetRenderer(filename,6,1));
		////entity4->AddComponent(new PlayerMoveScript());

		//SpriteRenderer* sprite2 = (SpriteRenderer*)entity4->GetComponent(ComponentType::RENDER_COMPONENT);

		////entity4->AddComponent(new BoxCollider());
		//entity4->AddComponent(new RigidBody(eBodyType::DYNAMIC));
		//entity4->AddComponent(new CircleCollider());
		//entity4->transform.position = Vector3(0, 0, 0);
		//entity4->transform.scale = Vector2(1, 1);
	}

#pragma endregion

#pragma region SystemStart
	systemManager->Start();
#pragma endregion
}

void World::Update(float deltaTime)
{
	systemManager->UpdateSystems(deltaTime);
}

void World::Render()
{
	systemManager->Render();
}

void World::Clean()
{
	entityManager->Clean();
	systemManager->CleanSystem();

	delete systemManager;
	delete entityManager;
}
