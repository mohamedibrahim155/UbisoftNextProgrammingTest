#include "stdafx.h"
#include "GoalPost.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/LevelManager/LevelManager.h"
GoalPost::GoalPost(const Vector2& spawnPosition) : BaseScriptComponent()
{
	m_spawnPosition = spawnPosition;
}

void GoalPost::start()
{
	
	createGoalHole();
	subscribeOnTrigger();
}

void GoalPost::updateComponent()
{
}

bool GoalPost::hasTargetReached()
{
	return hasReached;
}

void GoalPost::createGoalHole()
{
	gameObject->setTag("Goal");

	// creates components
	pSprite = new SpriteRenderer(SPRITE_PATH,Vector2::Zero(), 3);
	pCircleCollider = new CircleCollider();
	pRigidbody = new RigidBody(eBodyType::STATIC);

	
	// Add components
	gameObject->addComponent(pSprite);
	gameObject->addComponent(pRigidbody);
	gameObject->addComponent(pCircleCollider);

	pCircleCollider->setRadius(50);
	pCircleCollider->SetTrigger(true);


	gameObject->transform.position = m_spawnPosition;
}

void GoalPost::subscribeOnTrigger()
{
	pCircleCollider->OnTrigger.Subscribe([this](Collider* collider)
		{
			onTrigger(collider);
		});
}

void GoalPost::onTrigger(Collider* collider)
{
	if (collider->getEntity()->getTag() == "Ball")
	{
		LevelManager::GetInstance().queSceneChange(MAINMENU);
	}
}

void GoalPost::targetReached()
{
	//hasTargetReached = true;
}

