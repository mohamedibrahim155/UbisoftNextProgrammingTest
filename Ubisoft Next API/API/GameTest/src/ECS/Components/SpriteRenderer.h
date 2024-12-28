#pragma once
#include "RenderComponent.h"
#include "src/ECS/Entity.h"
class SpriteRenderer : public RenderComponent
{
public:
	SpriteRenderer(std::string filename);
	SpriteRenderer(std::string filename, Vector2 offset);
	SpriteRenderer(std::string filename, Vector2 offset, int order);
	
	// Inherited via RenderComponent
	virtual ~SpriteRenderer() override;
	virtual void Start() override;
	virtual void UpdateComponent() override;
	virtual void Render() override;
	 int RenderOrder() override;

	 virtual SpriteRenderer* Clone() const override;

	 void SetColor(const Vector3&  color);
	 void SetColor(const float& r, const float& g, const float& b);
	 void SetPosition(const Vector3&  position);
	 void SetRotation(const float& rotationY);
	 void SetOffset(const Vector2& offset);
	 void SetScale(const Vector2&  scale);
	 void SetOrder(int order);

	 int GetSpriteOrder() const;
	 Vector3 GetColor() const;
	 CSimpleSprite* GetSprite() const;
	 std::string GetFileName() const;


protected:

	 Vector3 color;
	 CSimpleSprite* sprite;
	 int spriteOrder = 0;

	 CSimpleSprite* CreateSprite(std::string filename, int colum, int row);

	
};

