#pragma once
#include "../Component.h"
#include "../App/SimpleSprite.h"
#include "src/Vector.h"


class RenderComponent : public IComponent
{
public:
	RenderComponent(std:: string filename, Vector2 position);
	RenderComponent(Vector2 position);
	RenderComponent(std:: string filename);

	virtual ~RenderComponent() override {};
	// Inherited via IComponent
	virtual void Start() override {};
	virtual void UpdateComponent() override {};
	virtual void Render() override {};


protected:
	std::string fileName;
	Vector2 centerScreen;
	Vector2 spriteOffset;
};

