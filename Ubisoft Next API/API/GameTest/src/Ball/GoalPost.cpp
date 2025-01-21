#include "stdafx.h"
#include "GoalPost.h"
#include "../src/ECS/Components/Collider/BoxCollider.h"
#include "../src/LevelManager/LevelManager.h"
#include "../src/GameManager/GameManager.h"
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
	checkGoalReached();
}

void GoalPost::checkGoalReached()
{

	if (m_hasReached)
	{
		if (m_delayTime <= 0)
		{

			reset();
			GameManager::GetInstance().showLevelComplete();
			return;
		}
		else
		{
			m_delayTime -= Timer::GetInstance().deltaTime;
		}
	}
}

void GoalPost::reset()
{
	m_delayTime = 0;
	m_hasReached = false;
}

void GoalPost::createGoalHole()
{
	gameObject->setTag("Goal");

	// creates components
	pSprite = new SpriteRenderer(SPRITE_PATH,Vector2::Zero(), 3);
	pCircleCollider = new CircleCollider();
	pRigidbody = new RigidBody(eBodyType::STATIC);
	pParticle = new ParticleComponent(DEFAULT_CIRCLE_PATH, 50, 1);

	pParticle->m_colorX = 1;
	pParticle->m_colorY = 1;
	pParticle->m_colorZ = 1;
	pParticle->m_spawnRadius = 1;
	pParticle->m_gravity = -3;
	pParticle->m_scale = 0.02f;

	pParticle->m_startVelocityX = { -300, 300 };
	pParticle->m_startVelocityY = { -300, 300 };
	pParticle->m_startTime = { 0.5,1 };
	pParticle->playOnAwake = false;

	
	// Add components
	gameObject->addComponent(pSprite);
	gameObject->addComponent(pRigidbody);
	gameObject->addComponent(pCircleCollider);
	gameObject->addComponent(pParticle);

	pCircleCollider->setRadius(80);
	pCircleCollider->SetTrigger(true);


	gameObject->transform.position = m_spawnPosition;
	gameObject->transform.scale = Vector2(0.4f, 0.4f);
}

void GoalPost::subscribeOnTrigger()
{
	pCircleCollider->OnTriggerEnter.Subscribe([this](Collider* collider)
		{
			onTriggerEnter(collider);
		});
}

void GoalPost::onTriggerEnter(Collider* collider)
{
	if (collider->getEntity()->getTag() == "Ball")
	{
		
		
			//targetReached();
			pParticle->Play();

			collider->getEntity()->setActive(false);
			targetReached();
		
	}
}

void GoalPost::targetReached()
{
	m_hasReached = true;

	// update score
	GameManager::GetInstance().updateScore();
}

