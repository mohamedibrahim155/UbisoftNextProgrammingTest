#pragma once
#include "../App/app.h"
#include "../src/ECS/Components/Transform.h"
#include "../src/ECS/Components/Renders/SpriteRenderer.h"
#include "../../Enums/EShapes.h"
#include "../src/Events/Event.h"

struct  SBox 
{
	Vector2 minimum;
	Vector2 maximum;

	SBox() = default;
	SBox(const Vector2& minimum, const Vector2& maximum)
		: minimum(minimum), maximum(maximum)
	{};

	Vector2 GetCenter()
	{
		float centerX = (minimum.x + maximum.x) * 0.5f;
		float centerY = (minimum.y + maximum.y) * 0.5f;

		return Vector2(centerX, centerY);
	}


};

struct SCircle
{
	Vector2 centre;
	float radius;

	SCircle() = default;

	SCircle(const Vector2& centre, float radius) :
		centre(centre), radius(radius)
	{};
};

struct SLine
{
	Vector2 startPoint;
	Vector2 endPoint;
	SLine() = default;

	SLine(const Vector2& startPoint, const Vector2& endPoint) :
		startPoint(startPoint), endPoint(endPoint)
	{};

	Vector2 Getcenter()
	{
		Vector2 midpoint = (startPoint + endPoint) * 0.5f;

		return midpoint;
	}
};

class Collider :  public  IComponent
{
public:
	Collider(eShape type);
	virtual ~Collider() override = default;
	virtual void start() {};
	virtual void Init();
	virtual void updateComponent() {};
	virtual void render(bool isDebugVisible) override {};
	virtual void cleanUp() override;
	virtual Collider* clone() const override =0;
	virtual eShape GetShapeType() const { return m_shape; };
	virtual SBox getBounds() = 0;
	virtual void calculateShape() = 0;

	bool IsTrigger() const { return m_isTrigger; };

	void SetTrigger(bool trigger);

	CEvent<Collider*> OnCollision;
	CEvent<Collider*> OnTrigger;
protected:

	bool m_isTrigger = false;
	eShape m_shape;

	Transform* transform = nullptr;
	SpriteRenderer* spriteRenderer = nullptr;

	Vector2  m_offset;
	Vector2 m_screenCenter;
	Vector2 m_scale{ 1,1 };

	

};

