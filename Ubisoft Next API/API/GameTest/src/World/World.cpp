#include "stdafx.h"
#include "World.h"
#include "../src/ECS/Systems/RenderSystem.h"
#define ASSET_PATH std::string(".\\Assets\\")
World::World()
{
	systemManager = new SystemManager();


#pragma region Systems

	RenderSystem* renderSystem = new RenderSystem();
	systemManager->RegisterSystem(renderSystem);
#pragma endregion


#pragma region Entities

	Entity* entity1 = new Entity();
	std::string filename = ASSET_PATH + "IdleBLUE- 150ms - 32x32.png";
	entity1->AddComponent(new Transform());
	entity1->AddComponent(new RenderComponent(filename));



#pragma endregion

#pragma region RegisterEntitesToSystem

	systemManager->AddEntity(entity1);
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
	systemManager->CleanSystem();
}
