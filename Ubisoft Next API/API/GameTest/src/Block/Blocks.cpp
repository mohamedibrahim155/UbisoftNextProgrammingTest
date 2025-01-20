#include "stdafx.h"
#include "Blocks.h"

Block::Block(eColorType type) : BaseScriptComponent(), m_type(type)
{
	pSprite = nullptr;
	pCollider = nullptr;
	pRigidbody = nullptr;
}

void Block::start()
{
	createBlock();
	changeType(m_type);
}

void Block::updateComponent()
{
}

void Block::changeType(eColorType newType)
{

	m_type = newType;
	changeSprite(newType);
}

void Block::changeSprite(eColorType type)
{
	if (!pSprite) return;

	Vector2 color = Vector2::One();
	switch (type)
	{
	case eColorType::WHITE:
		color = Vector2::One();
		break;
	case  eColorType::BLACK:
		color *=0.5f;
		break;
	}
	pSprite->setColor(color);
}

void Block::setTriggerState(bool state)
{
	if (!pCollider) return;

	pCollider->SetTrigger(state);
}

bool Block::isTrigger()
{
	if (!pCollider) return false;

	return pCollider->IsTrigger();
}

void Block::createBlock()
{
	gameObject->setTag("Block");

	// create components
	pSprite = (SpriteRenderer*)gameObject->getComponent(eComponentType::RENDER_COMPONENT);
	pCollider = new BoxCollider();
	pRigidbody = new RigidBody(eBodyType::STATIC);


	// adds components
	gameObject->addComponent(pCollider);
	gameObject->addComponent(pRigidbody);
}
