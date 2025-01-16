#pragma once
#include "../../Component.h"

struct sParticleData
{
	CSimpleSprite* sprite = nullptr;
	Vector2 velocity;
	float lifeTime =0;
	float gravity =0;
	float size;
	bool isActive = true;
};



class ParticleComponent : public IComponent
{
public:
	ParticleComponent(const std::string& filename, int totalParticles,int row);
	~ParticleComponent() override;

	// Inherited via IComponent
	void start() override;
	void updateComponent() override;
	void render(bool isDebugRender) override;
	void cleanUp() override;
	ParticleComponent* clone() const override;


	int totalParticles = 10;

	bool m_isLoop = false;
	bool isPlaying = false;

	Vector2 m_startVelocityX = { -100, 100 };
	Vector2 m_startVelocityY = { -100, 100 };

	//Vector2 mOriginInit;
	Vector2 m_startTime = { 0,2 };

	float m_gravity = 0;
	float m_spawnRadius = 50;
	float m_scale = 1;

	float m_colorX = 1;
	float m_colorY = 1;
	float m_colorZ = 1;

private:
	std::vector<sParticleData> m_listOfParticles;
	std::string fileName;
	int row;

	void ResetParticle(sParticleData& particle);

	float centerScreenX;
	float centerScreenY;
	
};

