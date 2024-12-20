#pragma once
#include "../src/ECS/Component.h"
#include "../src/ECS/Components/Transform.h"
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

class Collider :  public  IComponent
{
public:
	
	Collider(eShape type, Transform* transform);
	~Collider() = default ;
	virtual void Start() {};
	virtual void UpdateComponent() {};
	virtual void Render() {};

	virtual eShape GetShapeType() const { return shape; };
	virtual SBox GetBounds() = 0;
	virtual void CalculateShape() = 0;

	bool IsTrigger() const { return isTrigger; };

	void SetTrigger(bool trigger) { isTrigger = trigger; };

protected:

	eShape shape;
	bool isTrigger = false;
	Transform* transform;
	Vector2  offset;

	Vector2 center;

};

