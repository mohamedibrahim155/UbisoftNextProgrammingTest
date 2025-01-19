#include "stdafx.h"
#include "Level2.h"
#include "../src/ECS/Systems/Render/RenderSystem.h"
#include "../src/ECS/Systems/CustomScripts/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/Movement/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"

void Level2::start()
{


	


}

void Level2::cleanScene()
{
	systemManager->cleanSystem();
	entityManager->clean();
}

bool Level2::isLevelCompleted()
{
	return false;
}

