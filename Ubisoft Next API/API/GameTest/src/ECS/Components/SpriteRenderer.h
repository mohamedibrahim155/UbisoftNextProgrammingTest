#pragma once
#include "RenderComponent.h"
#include "src/ECS/Entity.h"
class SpriteRenderer : public RenderComponent
{
public:
	SpriteRenderer(std::string filename);
	SpriteRenderer(std::string filename, Vector3 position, Vector2 offset);
	SpriteRenderer(std::string filename, Vector3 position, Vector2 offset, int order);
	
	virtual ~SpriteRenderer() override;
	virtual void Start() override;
	virtual void UpdateComponent() override;
	virtual void Render() override;
	 int RenderOrder() override;

	 void SetColor(const Vector3&  color);
	 void SetPosition(const Vector3&  position);
	 void SetScale(const Vector2&  scale);
	 void SetOrder(int order);

	 int GetSpriteOrder() const;
	 Vector3 GetColor() const;
	 CSimpleSprite* GetSprite() const;


protected:

	 Vector3 color;
	 Vector3 spritePosition;
	 CSimpleSprite* sprite;
	 int spriteOrder = 0;

	 CSimpleSprite* CreateSprite(std::string filename, int colum, int row);
};

