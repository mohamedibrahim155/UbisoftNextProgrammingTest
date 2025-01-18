#include "stdafx.h"
#include "Level1.h"
#include "../src/ECS/Systems/Render/RenderSystem.h"
#include "../src/ECS/Systems/CustomScripts/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/Movement/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"
#include "../src/ECS/Components/Particle/ParticleComponent.h"
#include "../src/ECS/Components/Camera/Camera.h"
#include "../src/ECS/Components/Scripts/Ball.h"

void Level1::initialize()
{
	//Creation of gameobjects
#pragma region Entities

	Entity* entityWithBallScript = entityManager->createEntity();
	entityWithBallScript->addComponent(new Ball());





	for (size_t i = 0; i < 4; i++)
	{
		Entity* wallCollider = entityManager->createEntity();
		wallCollider->setTag("Wall");

		SpriteRenderer* sprite = new SpriteRenderer(ASSET_PATH + "\\IdleBLUE- 150ms - 32x32.png", Vector2::Zero(), 2);
		BoxCollider* wallBoxCollider = new BoxCollider();
		//wallBoxCollider->setSize(50,20);



		wallCollider->addComponent(sprite);
		wallCollider->addComponent(wallBoxCollider);
		wallCollider->addComponent(new RigidBody(eBodyType::STATIC));

		wallCollider->transform.position = Vector2(i*100, -200);
	}
	


	


#pragma endregion


}





void Level1::cleanScene()
{
	systemManager->cleanSystem();
}
