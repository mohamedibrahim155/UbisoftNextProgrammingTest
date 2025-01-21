#include "stdafx.h"
#include "Level2.h"
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
#include "../src/Block/Blocks.h"
#include "../src/Block/BlockHolder.h"
#include "../src/GameManager/GameManager.h"

Level2::Level2() : BaseLevel(LEVEL_2)
{
	m_centerScreen.x = APP_VIRTUAL_WIDTH / 2;
	m_centerScreen.y = APP_VIRTUAL_HEIGHT / 2;

	factory = new GameObjectFactory(entityManager);
}

Level2::~Level2()
{
	if (factory)
	{
		delete factory;
	}
}

void Level2::start()
{


	//Creation of gameobjects
#pragma region Entities


	createBackground();


	createWalls();

	createBlocks();





	// UI's
	Entity* entityWithGoalPost = entityManager->createEntity();
	goalPost = new GoalPost(Vector2(420, -300));
	entityWithGoalPost->addComponent(goalPost);

	Entity* entityWithScoreDisplayer = entityManager->createEntity();
	UIDisplayer* scoreUI = new UIDisplayer(eUIType::SCORE);
	entityWithScoreDisplayer->addComponent(scoreUI);
	entityWithScoreDisplayer->transform.position = Vector2(150, 350);

	Entity* entityWithStrike = entityManager->createEntity();
	UIDisplayer* strokeUI = new UIDisplayer(eUIType::STROKE);
	entityWithStrike->addComponent(strokeUI);
	entityWithStrike->transform.position = Vector2(300, 350);

	//Entity* entityWithlevelNumber = entityManager->createEntity();
	//UIDisplayer* LevelNumberUI = new UIDisplayer(eUIType::LEVELNUMBER);
	//entityWithlevelNumber->addComponent(LevelNumberUI);
	//entityWithlevelNumber->transform.position = Vector2(300, 350);




#pragma endregion


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

void Level2::createWalls()
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

void Level2::createBackground()
{
	factory->createBackground();
	factory->createBackgroundWhiteBorder();
}

void Level2::createBlocks()
{
	//Ball
	Entity* entityWithBallScript = entityManager->createEntity();
	BallComponent* ball1 = new BallComponent(entityManager, eColorType::WHITE);
	entityWithBallScript->addComponent(ball1);
	ball1->setSpawnPosition(-450, -310);


	Entity* entityWithBlockHolder = entityManager->createEntity();

	BlockHolder* blockHolder = new BlockHolder(ball1);


	// blocks
	Entity* entity1 = factory->createSpriteObject(BLOCK_2_PATH, Vector2::Zero(), -1);
	Block* block1 = new Block(eColorType::BLACK);
	entity1->addComponent(block1);
	entity1->transform.position = Vector2(-350, -300);
	entity1->transform.scale = Vector2(0.75, 0.75);



	Entity* entity2 = factory->createSpriteObject(BLOCK_3_PATH, Vector2::Zero(), -1);
	Block* block2 = new Block(eColorType::WHITE);
	entity2->addComponent(block2);
	entity2->transform.position = Vector2(-425, -200);
	entity2->transform.scale = Vector2(0.75, 0.75);





	Entity* entity3 = factory->createSpriteObject(BLOCK_3_PATH, Vector2::Zero(), -1);
	Block* block3 = new Block(eColorType::BLACK);
	entity3->addComponent(block3);
	entity3->transform.position = Vector2(395, -220);
	entity3->transform.scale = Vector2(0.75, 0.75);

	Entity* entity4 = factory->createSpriteObject(BLOCK_2_PATH, Vector2::Zero(), -1);
	Block* block4 = new Block(eColorType::WHITE);
	entity4->addComponent(block4);
	entity4->transform.position = Vector2(295, -296);
	entity4->transform.scale = Vector2(0.75, 0.75);


	Entity* entity5 = factory->createSpriteObject(BLOCK_2_PATH, Vector2::Zero(), -1);
	Block* block5 = new Block(eColorType::BLACK);
	entity5->addComponent(block5);
	entity5->transform.position = Vector2(27, -154);
	entity5->transform.scale = Vector2(1, 1);


	Entity* entity6 = factory->createSpriteObject(BLOCK_3_PATH, Vector2::Zero(), -1);
	Block* block6 = new Block(eColorType::BLACK);
	entity6->addComponent(block6);
	entity6->transform.position = Vector2(27, 254);
	entity6->transform.scale = Vector2(1.5, 1.5);


	Entity* entity7 = factory->createSpriteObject(BLOCK_2_PATH, Vector2::Zero(), -1);
	Block* block7 = new Block(eColorType::WHITE);
	entity7->addComponent(block7);
	entity7->transform.position = Vector2(295, 83);
	entity7->transform.scale = Vector2(1.25, 1.25);


	//// block holder
	blockHolder->addBlock(block1);
	blockHolder->addBlock(block2);
	blockHolder->addBlock(block3);
	blockHolder->addBlock(block4);
	blockHolder->addBlock(block5);
	blockHolder->addBlock(block6);
	blockHolder->addBlock(block7);

	//blockHolder->debugEnity = entity7;

	entityWithBlockHolder->addComponent(blockHolder);
	
}

