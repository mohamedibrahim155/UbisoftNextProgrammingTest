#include "stdafx.h"
#include "Level1.h"
#include "../src/ECS/Systems/RenderSystem.h"
#include "../src/ECS/Systems/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/ECS/Components/Scripts/PlayerMoveScript.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"
#include "../src/ECS/Components/Particle/ParticleComponent.h"
void Level1::initialize()
{
	systemManager->start();
	//Creation of gameobjects
#pragma region Entities

	std::string filename = ASSET_PATH + "IdleBLUE- 150ms - 32x32.png";
	std::string defaultCircle = ASSET_PATH + "\\Default\\circle-512.png";

	/*Entity* player = entityManager->createEntity();
	player->addComponent(new SpriteRenderer(filename,true));*/

	Entity* entity1 = entityManager->createEntity();

	ParticleComponent* particleComponent = new ParticleComponent(defaultCircle, 100, 1);

	entity1->transform.position = Vector2(-150, 50);
	particleComponent->m_colorX = 0;
	particleComponent->m_colorY = 0;
	particleComponent->m_colorZ = 1;
	particleComponent->m_spawnRadius = 1;
	particleComponent->m_Gravity = -3;
	particleComponent->m_scale = 0.005f;

	particleComponent->m_startVelocityX = { -300, 300 };
	particleComponent->m_startVelocityY = { -300, 300 };
	particleComponent->m_startTime = { 2,3 };
	particleComponent->isLoop = true;

	entity1->addComponent(particleComponent);


	Entity* entity2 = entityManager->createEntity();

	PlayerMoveScript* playerMoveScript = new PlayerMoveScript();
	entity2->addComponent(playerMoveScript);

#pragma endregion




	//Initialise Systems


}





void Level1::cleanScene()
{
	systemManager->cleanSystem();
}
