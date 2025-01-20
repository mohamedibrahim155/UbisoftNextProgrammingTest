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
	CheckLevelCompleteState();
}

void GoalPost::CheckLevelCompleteState()
{

	if (hasReached)
	{
		if (particleInvokeTime <= 0)
		{
			pParticle->Play();
			hasReached = false;
			//LevelManager::GetInstance().nextLevel();
			return;
		}
		else
		{
			particleInvokeTime -= Timer::GetInstance().deltaTime;
		}
	}
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
	pParticle->m_colorY = 0;
	pParticle->m_colorZ = 1;
	pParticle->m_spawnRadius = 1;
	pParticle->m_gravity = -3;
	pParticle->m_scale = 0.008f;

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
	gameObject->transform.scale = Vector2(0.5f, 0.5f);
}

void GoalPost::subscribeOnTrigger()
{
	pCircleCollider->OnTrigger.Subscribe([this](Collider* collider)
		{
			onTriggerStay(collider);
		});
}

void GoalPost::onTriggerStay(Collider* collider)
{
	if (collider->getEntity()->getTag() == "Ball")
	{
		if (!hasReached)
		{
			targetReached();
		}
	}
}

void GoalPost::targetReached()
{
	hasReached = true;
}

