#include "stdafx.h"
#include "World.h"
#include "../src/ECS/Systems/Render/RenderSystem.h"
#include "../src/ECS/Systems/CustomScripts/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/Movement/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/ECS/Systems/ParticleSystemRender/ParticleSystem.h"
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
	systemManager->registerSystem(renderSystem);
	systemManager->registerSystem(particleSystem);
#pragma endregion


}

void World::start()
{
	// Creates levels
	LevelManager::GetInstance().createLevels();

	//Sets the current scene to level 1
	LevelManager::GetInstance().queSceneChange(MAINMENU);
}

void World::update(float deltaTime)
{

	LevelManager::GetInstance().update(deltaTime);
}

void World::render()
{
	LevelManager::GetInstance().render();

}

void World::clean()
{
	LevelManager::GetInstance().cleanScene();
	
	delete systemManager;
	delete entityManager;
}
