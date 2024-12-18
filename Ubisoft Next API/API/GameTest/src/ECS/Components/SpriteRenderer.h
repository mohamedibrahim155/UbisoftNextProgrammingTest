#pragma once
#include "RenderComponent.h"
#include "src/ECS/Entity.h"
class SpriteRenderer : public RenderComponent
{
public:
	SpriteRenderer(std::string filename, Vector3 position, Vector2 offset);
	SpriteRenderer(std::string filename, Vector3 position, Vector2 offset, int order);
	~SpriteRenderer() override;
	 void Start() override;
	 void UpdateComponent() override;
	 void Render() override;

	 void SetColor(const Vector3&  color);
	 void SetPosition(const Vector3&  position);
	 void SetScale(const Vector2&  scale);
	 void SetOrder(int order);

	 int GetSpriteOrder() const;
	 Vector3 GetColor() const;
	 CSimpleSprite* GetSprite() const;


private:

	 Vector3 color;
	 Vector3 spritePosition;
	 CSimpleSprite* sprite;
	 int spriteOrder = 0;
};

