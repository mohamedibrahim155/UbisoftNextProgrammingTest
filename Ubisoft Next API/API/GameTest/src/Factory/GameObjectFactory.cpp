#include "stdafx.h"
#include "GameObjectFactory.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/ECS/Components/Collider/CircleCollider.h"
#include "../src/ECS/Components/Collider/LineCollider.h"
#include "../src/ECS/Components/UI/ButtonRenderer.h"


GameObjectFactory::GameObjectFactory(EntityManager* entityManager) :  m_entityManager(entityManager)
{
}

void GameObjectFactory::createBackground(const std::string& fileName)
{
	// Scaling factor for the sprite
	float scale = 0.5f;

	// Effective size of the scaled sprite
	float scaledSpriteWidth = 256 * scale;
	float scaledSpriteHeight = 256 * scale;

	// Calculate the number of rows and columns needed to fill the screen
	float row = APP_VIRTUAL_WIDTH / scaledSpriteWidth;
	float column = APP_VIRTUAL_HEIGHT / scaledSpriteHeight;

	// Center of the screen
	Vector2 centerScreen = Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);


	for (int x = 0; x < row +1 ; x++)
	{
		for (int y = 0; y < column +1 ; y++)
		{
			Vector2 position = Vector2(x * scaledSpriteWidth, y * scaledSpriteHeight) - centerScreen;
			Entity* bgSprite = createSpriteObject(fileName, position, -1);

			bgSprite->transform.scale = Vector2(scale, scale);
		}
	}
}

Entity* GameObjectFactory::createPhysicsObject(eShape shape, eBodyType bodyType)
{
	Entity* physicsEntity = m_entityManager->createEntity();

	Collider* collider = createCollider(shape);
	RigidBody* rigidbody = new RigidBody(bodyType);

	physicsEntity->addComponent(collider);
	physicsEntity->addComponent(rigidbody);

	return physicsEntity;
}

Entity* GameObjectFactory::createPhysicsObjectWithSprite(const std::string& filenmame, 
	const Vector2& offset, int spriteOrder, eShape shape, eBodyType bodyType)
{
	Entity* Object = createSpriteObject(filenmame, offset, spriteOrder);
	Object->addComponent(createCollider(shape));
	Object->addComponent(new RigidBody(bodyType));

	return Object;
}



Entity* GameObjectFactory::createSpriteObject(const std::string& filenmame,
	const Vector2& offset, int spriteOrder)
{
	Entity* spriteObject = m_entityManager->createEntity();

	SpriteRenderer* sprite = new SpriteRenderer(filenmame, offset, spriteOrder);

	spriteObject->addComponent(sprite);

	return spriteObject;
}

Entity* GameObjectFactory::createButton(const std::string& filename)
{
	Entity* entity = m_entityManager->createEntity();

	ButtonRenderer* buttonRender = new ButtonRenderer(filename, nullptr);



	return entity;
}

Entity* GameObjectFactory::createButtonWithText(const std::string& filename, const std::string& message, const Vector3& textColor)
{
	Entity* entity = m_entityManager->createEntity();

	TextRenderer* text = createText(message,textColor, eFontType::BITMAP_TIMES_ROMAN_10);

	ButtonRenderer* buttonRender = new ButtonRenderer(filename, text);

	entity->addComponent(buttonRender);
	return entity;
}

Entity* GameObjectFactory::createButtonWithText(const std::string& filename, const std::string& message, const Vector3& textColor, const std::string& tag)
{
	Entity* entity = m_entityManager->createEntity();
	entity->setTag(tag);
	TextRenderer* text = createText(message, textColor, eFontType::BITMAP_TIMES_ROMAN_10);

	ButtonRenderer* buttonRender = new ButtonRenderer(filename, text);

	entity->addComponent(buttonRender);
	return entity;
}

Collider* GameObjectFactory::createCollider(eShape shape)
{
	switch (shape)
	{
	case eShape::BOX:
		return new BoxCollider();
	case eShape::CIRCLE:
		return  new CircleCollider();
	case eShape::LINE:
		return  new LineCollider();
	}
	return nullptr;
}

TextRenderer* GameObjectFactory::createText(const std::string& message, const Vector3& textColor, eFontType fontType)
{

	TextRenderer* text = new TextRenderer(message, Vector2::Zero(), textColor, fontType);
	return text;
}
