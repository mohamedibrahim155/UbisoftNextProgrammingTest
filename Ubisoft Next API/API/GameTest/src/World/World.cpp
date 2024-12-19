#include "stdafx.h"
#include "World.h"
#include "../src/ECS/Systems/RenderSystem.h"
#include "../src/ECS/Systems/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/MovementSystem.h"
#include "../src/ECS/Components/Scripts/PlayerMoveScript.h"
#include "../src/Utils/Utils.h"

World::World()
{
	systemManager = new SystemManager();
	entityManager = new EntityManager(systemManager);


#pragma region Systems

	ISystem* renderSystem = new RenderSystem();
	ISystem* customScriptSystem = new CustomScriptsControllerSystem();
	ISystem* movementSystem = new MovementSystem();

	systemManager->RegisterSystem(customScriptSystem);
	systemManager->RegisterSystem(movementSystem);
	systemManager->RegisterSystem(renderSystem);
#pragma endregion







}

void World::Start()
{
#pragma region Entities


	std::string filename = ASSET_PATH + "IdleBLUE- 150ms - 32x32.png";

	for (size_t i = 0; i < 5; i++)
	{
		float randomWidth = Random::RandomRange(-(float)APP_VIRTUAL_WIDTH, (float)APP_VIRTUAL_WIDTH);
		float randomheight = Random::RandomRange(-(float)APP_VIRTUAL_HEIGHT, (float)APP_VIRTUAL_HEIGHT);
		Entity* entity1 = entityManager->CreateEntity();
		//entity1->AddComponent(new SpriteRenderer(filename, Vector3::Zero(), Vector2::Zero()));
		entity1->AddComponent(new PlayerMoveScript());
		entity1->transform.position = Vector3(randomWidth, randomheight, 0);

		Entity* entity2 = entityManager->CreateEntity();
		entity2->AddComponent(new SpriteRenderer(filename, Vector3::Zero(), Vector2::Zero()));

		randomWidth = Random::RandomRange(-(float)(APP_VIRTUAL_WIDTH / 2), (float)(APP_VIRTUAL_WIDTH / 2));
		randomheight = Random::RandomRange(-(float)(APP_VIRTUAL_HEIGHT / 2), (float)(APP_VIRTUAL_HEIGHT / 2));
		entity2->transform.position = Vector3(randomWidth, randomheight, 0);
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
