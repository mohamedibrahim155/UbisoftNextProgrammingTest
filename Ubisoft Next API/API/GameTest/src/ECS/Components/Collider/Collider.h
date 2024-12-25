#pragma once
#include "../App/app.h"
#include "../src/ECS/Components/Transform.h"
#include "../src/ECS/Components/SpriteRenderer.h"

enum class eShape
{
	BOX,
	CIRCLE,
	LINE,
};


struct  SBox 
{
	Vector2 minimum;
	Vector2 maximum;

	SBox() = default;
	SBox(const Vector2& minimum, const Vector2& maximum)
		: minimum(minimum), maximum(maximum)
	{};


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


};

class Collider :  public  IComponent
{
public:
	Collider(eShape type);
	~Collider() override = default ;
	virtual void Start() {};
	virtual void Init();
	virtual void UpdateComponent() {};
	virtual void Render() {};
	virtual Collider* Clone() const override =0;

	virtual eShape GetShapeType() const { return shape; };
	virtual SBox GetBounds() = 0;
	virtual void CalculateShape() = 0;

	bool IsTrigger() const { return isTrigger; };

	void SetTrigger(bool trigger);

protected:

	bool isTrigger = false;
	eShape shape;

	Transform* transform;
	SpriteRenderer* spriteRenderer;

	Vector2  offset;
	Vector2 center;
	Vector2 mScale{ 1,1 };




};

