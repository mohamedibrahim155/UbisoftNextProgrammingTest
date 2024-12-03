#pragma once
#include "./src/Entities/Entity.h"
#include "../App/SimpleSprite.h"
#include "src/Vector.h"
class CGameObject : public CEntity
{
public:
	CGameObject();
	CGameObject(CSimpleSprite* sprite);
	~CGameObject();
	virtual void Start();
	virtual void Update();
	virtual void OnDestroy();
	virtual void Clean();
	virtual void Render();
	virtual void Destroy();
	virtual void CopyFromOther(CGameObject* other);

	void SetPosition(float x, float y);
	void SetScale(float value);
	void SetSprite(CSimpleSprite* sprite);

	Vector2 GetPosition();

	std::string m_tag = "Untagged";
	std::string m_name = "unNamed";

	


private:

	CSimpleSprite* m_sprite;
	Vector2 position;

};

