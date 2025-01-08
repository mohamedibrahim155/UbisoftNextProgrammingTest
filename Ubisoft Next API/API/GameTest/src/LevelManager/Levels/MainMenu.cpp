#include "stdafx.h"
#include "MainMenu.h"
#include "../src/ECS/Systems/RenderSystem.h"
#include "../src/ECS/Systems/CustomScriptsControllerSystem.h"
#include "../src/ECS/Systems/MovementSystem.h"
#include "../src/ECS/Systems/Physics/PhysicsSystem.h"
#include "../src/ECS/Components/Scripts/PlayerMoveScript.h"
#include "../src/ECS/Components/Scripts/PoolTestingScript.h"
#include "../src/Utils/Utils.h"
#include "../src/Utils/PhysicsUtils.h"
void MainMenu::initialize()
{
	systemManager->start();

	Entity* buttonRender = entityManager->createEntity();

	TextRenderer* text = new TextRenderer("Heyo");
	text->setColor(1, 0, 0);
	buttonRender->addComponent(new ButtonRenderer(ASSET_PATH + "Default\\square-rounded-512.png", text));
	buttonRender->transform.position = Vector3(0, 100, 0);
	buttonRender->transform.scale = Vector2(0.3f, 0.3f);
	buttonRender->addComponent(new PlayerMoveScript());
	ButtonRenderer* button = dynamic_cast<ButtonRenderer*>(buttonRender->getComponent(ComponentType::RENDER_COMPONENT));

	button->addListenersOnButtonPress([this]()
		{
			Entity* firstEntity = entityManager->createEntity();

			float randomWidth = Random::RandomRange(-(float)APP_VIRTUAL_WIDTH, (float)APP_VIRTUAL_WIDTH);
			float randomheight = Random::RandomRange(-(float)APP_VIRTUAL_HEIGHT, (float)APP_VIRTUAL_HEIGHT);
			firstEntity->addComponent(new SpriteSheetRenderer(ASSET_PATH + "IdleBLUE- 150ms - 32x32.png", 6, 1));
			//firstEntity->addComponent(new PlayerMoveScript());
			firstEntity->addComponent(new RigidBody(eBodyType::DYNAMIC));
			firstEntity->addComponent(new CircleCollider());
			firstEntity->transform.position = Vector3(randomWidth / 2, randomWidth / 2, 0);



		});

	Entity* entityWithPool = entityManager->createEntity();
	entityWithPool->setTag("PoolManager");
	entityWithPool->addComponent(new PoolTestingScript(entityManager));


}

void MainMenu::cleanScene()
{
	systemManager->cleanSystem();
}
