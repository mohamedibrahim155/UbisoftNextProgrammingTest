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
#include "../src/Ball/Ball.h"
#include "../src/Ball/GoalPost.h"

Level1::Level1() : BaseLevel(LEVEL_1)
{
	m_centerScreen.x = APP_VIRTUAL_WIDTH / 2;
	m_centerScreen.y = APP_VIRTUAL_HEIGHT / 2;

	factory = new GameObjectFactory(entityManager);
}

Level1::~Level1()
{
	if (factory)
	{
		delete factory;
	}
}

void Level1::start()
{
	//Creation of gameobjects
#pragma region Entities


	createBackground();

	Entity* entityWithBallScript = entityManager->createEntity();
	Ball* ball1 = new Ball(entityManager);
	entityWithBallScript->addComponent(ball1);
	ball1->setSpawnPosition(-300, 200);

	Entity* entityWithBallScript2 = entityManager->createEntity();

	Ball* ball2 = new Ball(entityManager);
	entityWithBallScript2->addComponent(ball2);

	ball2->setSpawnPosition(-300, 100);


	Entity* entityWithGoalPost = entityManager->createEntity();
	goalPost = new GoalPost(Vector2(300, 50));
	entityWithGoalPost->addComponent(goalPost);

	createWalls();


#pragma endregion


}

void Level1::createWalls()
{
	Entity* wallCollider = entityManager->createEntity();
	wallCollider->setTag("Wall Left");
	BoxCollider* wallBoxCollider = new BoxCollider();
	wallBoxCollider->setSize(10, 768);

	wallCollider->addComponent(wallBoxCollider);
	wallCollider->addComponent(new RigidBody(eBodyType::STATIC));
	wallCollider->transform.position = Vector2(m_centerScreen.x, 0);


	Entity* wallCollider2 = entityManager->createEntity();
	wallCollider2->setTag("Wall Right ");
	BoxCollider* wallBoxCollider2 = new BoxCollider();
	wallBoxCollider2->setSize(10, 768);

	wallCollider2->addComponent(wallBoxCollider2);
	wallCollider2->addComponent(new RigidBody(eBodyType::STATIC));
	wallCollider2->transform.position = Vector2(-m_centerScreen.x, 0);



	Entity* wallCollider3 = entityManager->createEntity();
	wallCollider3->setTag("Wall Top ");
	BoxCollider* wallBoxCollider3 = new BoxCollider();
	wallBoxCollider3->setSize(m_centerScreen.x * 2, 10);

	wallCollider3->addComponent(wallBoxCollider3);
	wallCollider3->addComponent(new RigidBody(eBodyType::STATIC));
	wallCollider3->transform.position = Vector2(0, m_centerScreen.y);


	Entity* wallCollider4 = entityManager->createEntity();
	wallCollider4->setTag("Wall Bottom ");
	BoxCollider* wallBoxCollider4 = new BoxCollider();
	wallBoxCollider4->setSize(m_centerScreen.x * 2, 10);

	wallCollider4->addComponent(wallBoxCollider4);
	wallCollider4->addComponent(new RigidBody(eBodyType::STATIC));
	wallCollider4->transform.position = Vector2(0, -m_centerScreen.y);
}

void Level1::createBackground()
{
	float row = APP_VIRTUAL_WIDTH / 256;
	float column = APP_VIRTUAL_HEIGHT / 256;

	for (int x = 0; x < row+1; x++)
	{
		for (int y = 0; y < column+1; y++)
		{
			Vector2 position = Vector2(x * 256, y * 256) - m_centerScreen ;
			Entity* bgSprite = factory->createSpriteObject(BACKGROUND_PATH, position, 0);

		}
	}

}



bool Level1::isLevelCompleted()
{
	if (!goalPost) return false;
	
	return goalPost->hasTargetReached();
}





void Level1::cleanScene()
{
	systemManager->cleanSystem();
	entityManager->clean();
}
