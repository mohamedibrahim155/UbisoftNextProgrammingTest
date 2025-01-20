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
#include "../src/UI/UIDisplayer.h"

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


	createWalls();

	createBlocks();



	Entity* entityWithBallScript = entityManager->createEntity();
	Ball* ball1 = new Ball(entityManager);
	entityWithBallScript->addComponent(ball1);
	ball1->setSpawnPosition(-300, 200);


	Entity* entityWithGoalPost = entityManager->createEntity();
	goalPost = new GoalPost(Vector2(300, 50));
	entityWithGoalPost->addComponent(goalPost);

	Entity* entityWithScoreDisplayer = entityManager->createEntity();
	UIDisplayer* scoreUI = new UIDisplayer(eUIType::SCORE);
	entityWithScoreDisplayer->addComponent(scoreUI);
	entityWithScoreDisplayer->transform.position = Vector2(150, 350);

	Entity* entityWithStrike= entityManager->createEntity();
	UIDisplayer* strokeUI = new UIDisplayer(eUIType::STROKE);
	entityWithStrike->addComponent(strokeUI);
	entityWithStrike->transform.position = Vector2(300, 350);
#pragma endregion


}

void Level1::createWalls()	
{
	Entity* wallCollider = entityManager->createEntity();
	wallCollider->setTag("Wall Left");
	BoxCollider* wallBoxCollider = new BoxCollider();
	wallBoxCollider->setSize(50, 768);

	wallCollider->addComponent(wallBoxCollider);
	wallCollider->addComponent(new RigidBody(eBodyType::STATIC));
	wallCollider->transform.position = Vector2(m_centerScreen.x, 0);


	Entity* wallCollider2 = entityManager->createEntity();
	wallCollider2->setTag("Wall Right ");
	BoxCollider* wallBoxCollider2 = new BoxCollider();
	wallBoxCollider2->setSize(50, 768);

	wallCollider2->addComponent(wallBoxCollider2);
	wallCollider2->addComponent(new RigidBody(eBodyType::STATIC));
	wallCollider2->transform.position = Vector2(-m_centerScreen.x, 0);



	Entity* wallCollider3 = entityManager->createEntity();
	wallCollider3->setTag("Wall Top ");
	BoxCollider* wallBoxCollider3 = new BoxCollider();
	wallBoxCollider3->setSize(m_centerScreen.x * 2, 50);

	wallCollider3->addComponent(wallBoxCollider3);
	wallCollider3->addComponent(new RigidBody(eBodyType::STATIC));
	wallCollider3->transform.position = Vector2(0, m_centerScreen.y);


	Entity* wallCollider4 = entityManager->createEntity();
	wallCollider4->setTag("Wall Bottom ");
	BoxCollider* wallBoxCollider4 = new BoxCollider();
	wallBoxCollider4->setSize(m_centerScreen.x * 2, 50);

	wallCollider4->addComponent(wallBoxCollider4);
	wallCollider4->addComponent(new RigidBody(eBodyType::STATIC));
	wallCollider4->transform.position = Vector2(0, -m_centerScreen.y);
}

void Level1::createBackground()
{
	factory->createBackground();
	factory->createBackgroundWhiteBorder();


	factory->createSpriteObject(LEVEL_ONE_PATH,Vector2::Zero(),-1);
}

void Level1::createBlocks()
{
	Entity* block1 = factory->createPhysicsObject(eShape::BOX, eBodyType::STATIC);
	BoxCollider* collider = factory->AsBox(block1);

	collider->setSize(53,53);
	block1->transform.position = Vector2(-113,-17);

	Entity* block2 = factory->createPhysicsObject(eShape::BOX, eBodyType::STATIC);
	BoxCollider* collider2 = factory->AsBox(block2);

	collider2->setSize(53, 53);
	block2->transform.position = Vector2(197, 185);


	Entity* block3 = factory->createPhysicsObject(eShape::BOX, eBodyType::STATIC);
	BoxCollider* collider3 = factory->AsBox(block3);

	collider3->setSize(53, 53);
	block3->transform.position = Vector2(138, -147);
}



bool Level1::isLevelCompleted()
{
	
	return false;

}





void Level1::cleanScene()
{
	systemManager->cleanSystem();
	entityManager->clean();
}
