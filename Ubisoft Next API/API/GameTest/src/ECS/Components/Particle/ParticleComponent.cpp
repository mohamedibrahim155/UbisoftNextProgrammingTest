#include "stdafx.h"
#include "../src/ECS/Entity.h"
#include "ParticleComponent.h"
#include "../src/Utils/Utils.h"
#include "../src/Timer/Timer.h"
ParticleComponent::ParticleComponent(const std::string& filename, 
	int totalParticles, int row) :
	IComponent(eComponentType::PARTICLE_COMPONENT), 
	totalParticles(totalParticles),
	row(row), 
	fileName(filename)
{
	centerScreenX = APP_VIRTUAL_WIDTH / 2;
	centerScreenY = APP_VIRTUAL_HEIGHT / 2;

	for (int i = 0; i < totalParticles; i++)
	{
		sParticleData data;

		data.sprite = App::CreateSprite(fileName.c_str(), 1, row);

		std::vector<int> frames;
		for (int i = 0; i < row; i++)
		{
			frames.push_back(i);
		}
		data.sprite->CreateAnimation(0, 1.0f / 6.0f, frames);
		data.sprite->SetAnimation(0);

		m_listOfParticles.push_back(data);
	}
}

ParticleComponent::~ParticleComponent()
{


}

void ParticleComponent::start()
{
	if (!playOnAwake) return;

	for (sParticleData& data : m_listOfParticles)
	{
		ResetParticle(data);
	}
	
}

void ParticleComponent::updateComponent()
{
	if (!m_isEnabled) return;


	if (m_isLoop)
	{
		int lastIndex = m_listOfParticles.size() - 1;

		if (!m_listOfParticles[lastIndex].isActive)
		{
			for (sParticleData& data : m_listOfParticles)
			{
				ResetParticle(data);
			}
		}

	}

	for (sParticleData& data : m_listOfParticles)
	{
		if (!data.isActive) continue;	

		float x, y;

		data.sprite->GetPosition(x, y);

		data.gravity -= m_gravity  * Timer::GetInstance().deltaTime;

		y -= data.gravity;

		x += data.velocity.x * Timer::GetInstance().deltaTime;
		y += data.velocity.y * Timer::GetInstance().deltaTime;


		data.sprite->SetPosition(x, y);

		data.sprite->SetScale(m_scale);

		data.sprite->SetColor(m_colorX, m_colorY, m_colorZ);

		data.lifeTime -= Timer::GetInstance().deltaTime;

		if (data.lifeTime <= 0)
		{
			data.isActive = false;
		}


		data.sprite->Update(Timer::GetInstance().deltaTime * 1000);
	}

	
	

}

void ParticleComponent::render(bool isDebugRender)
{
	if (!m_isEnabled) return;
	
	for (sParticleData& data : m_listOfParticles)
	{
		if (!data.isActive) continue;

		data.sprite->Draw();
	}

}

void ParticleComponent::cleanUp()
{
	for (sParticleData& paritcle :  m_listOfParticles)
	{
		if (paritcle.isActive)
		{
			paritcle.isActive = false;
		}

		if (paritcle.sprite)
		{
			delete paritcle.sprite;
		}
	}

	m_listOfParticles.clear();
}

void ParticleComponent::Play()
{
	for (sParticleData& data : m_listOfParticles)
	{
		ResetParticle(data);
	}
}

ParticleComponent* ParticleComponent::clone() const
{
	return  new ParticleComponent(this->fileName,this->totalParticles,this->row);
}

void ParticleComponent::ResetParticle(sParticleData& particle)
{
	if (!particle.isActive)
	{
		particle.isActive = true;
	}


	particle.velocity = Vector2(Random::RandomRange(m_startVelocityX.x, m_startVelocityX.y), 
		Random::RandomRange(m_startVelocityY.x, m_startVelocityY.y));

	particle.lifeTime = Random::RandomRange(m_startTime.x, m_startTime.y);
	particle.gravity = 0;

	Vector2 pos = Vector2(gameObject->transform.localPosition.x, gameObject->transform.localPosition.y);

	float x = Random::RandomRange(-1, 1);
	float y = Random::RandomRange(-1, 1);

	pos.x += x * m_spawnRadius;
	pos.y += y * m_spawnRadius;

	particle.sprite->SetPosition(pos.x +  centerScreenX , pos.y + centerScreenY);
	
}
