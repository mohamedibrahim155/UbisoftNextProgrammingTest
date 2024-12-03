#include "stdafx.h"
#include "GameObject.h"
#include "src/Timer/Timer.h"
CGameObject::CGameObject()
{
	m_sprite = nullptr;
	position = Vector2(0, 0);
}

CGameObject::CGameObject(CSimpleSprite* sprite) : m_sprite(sprite)
{
	position = Vector2(0, 0);
}

CGameObject::~CGameObject()
{
	Clean();
}

void CGameObject::Start()
{
}

void CGameObject::Update()
{
	if (!m_isEnabled) return;

	if (m_sprite == nullptr) return;

	// Updating Sprite data
	m_sprite->Update(Timer::GetInstance().deltaTime);
}

void CGameObject::OnDestroy()
{
	Clean();
}

void CGameObject::Clean()
{
	m_sprite = nullptr;
	delete m_sprite;
}

void CGameObject::Render()
{
	if (m_sprite != nullptr)
	{
		m_sprite->Draw();
	}

}

void CGameObject::Destroy()
{
	CEntity::Destroy();
}

void CGameObject::CopyFromOther(CGameObject* other)
{
	CEntity::CopyFromOther(other);

	this->m_tag = other->m_tag;
	this->m_sprite = other->m_sprite;
	this->m_name = other->m_name;
	this->position = other->position;
}

void CGameObject::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	if (m_sprite == nullptr) return;
	m_sprite->SetPosition(x, y);
}

void CGameObject::SetScale(float value)
{
	m_sprite->SetScale(value);
}

void CGameObject::SetSprite(CSimpleSprite* sprite)
{
	this->m_sprite = sprite;
}

Vector2 CGameObject::GetPosition()
{
	m_sprite->GetPosition(position.x, position.y);

	return position;
}


