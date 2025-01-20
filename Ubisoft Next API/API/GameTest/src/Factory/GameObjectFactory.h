#pragma once
#include "../src/ECS/EntityManager.h"
#include "../src/ECS/Components/Rigidbody/RigidBody.h"
#include "../src/ECS/Components/Collider/Collider.h"
#include "../src/ECS/Components/UI/TextRenderer.h"

class GameObjectFactory
{
public:
	GameObjectFactory(EntityManager* entityManager);
	~GameObjectFactory() = default;

	void createBackground(const std::string& fileName);
	Entity* createPhysicsObject(eShape shape, eBodyType bodyType);
	Entity* createPhysicsObjectWithSprite(const std::string& filenmame, const Vector2& offset, int spriteOrder, eShape shape, eBodyType bodyType);
	Entity* createSpriteObject(const std::string& filenmame, const Vector2& offset, int spriteOrder);

	Entity* createButton(const std::string& filename);
	Entity* createButtonWithText(const std::string& filename, const std::string& message, const Vector3& textColor = Vector3::One());
	Entity* createButtonWithText(const std::string& filename, const std::string& message, const Vector3& textColor, const std::string& tag);

private:

	EntityManager* m_entityManager;

	Collider* createCollider(eShape shape);
	TextRenderer* createText(const std::string& message, const Vector3& textColor, eFontType fontType);

};

