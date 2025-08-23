#pragma once
#include "RenderComponent.h"
#include "src/ECS/Entity.h"
class SpriteRenderer : public RenderComponent
{
public:
	SpriteRenderer(std::string filename, bool createSprite = false);
	SpriteRenderer(std::string filename, Vector2 offset);
	SpriteRenderer(std::string filename, Vector2 offset, int order);
	
	// Inherited via RenderComponent
	virtual ~SpriteRenderer() override;
	virtual void start() override;
	virtual void updateComponent() override;
	virtual void render(bool isDebugRender = false) override;
	virtual void cleanUp() override {};
	 int renderOrder() override;

	 virtual SpriteRenderer* clone() const override;

	 void setColor(const Vector3&  color);
	 void setColor(const float& r, const float& g, const float& b);
	 void setPosition(const Vector3&  position,  const Vector3& camerePosition);
	 void setRotation(const float& rotationY);
	 void setOffset(const Vector2& offset);
	 void setScale(const Vector2&  scale);
	 void setOrder(int order);

	 int getSpriteOrder() const;
	 Vector3 getColor() const;
	 CSimpleSprite* getSprite() const;
	 std::string getFileName() const;


protected:

	 Vector3 m_color;
	 CSimpleSprite* m_sprite;
	 int m_spriteOrder = 0;

	 CSimpleSprite* createSprite(std::string filename, int colum, int row);

	
};

