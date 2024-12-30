#pragma once
#include "../../Component.h"
#include "../App/SimpleSprite.h"
#include "src/Vector.h"

 //Base Class to Render components in Scene
class RenderComponent : public IComponent
{
public:
	RenderComponent(std:: string filename, Vector2 position);

	RenderComponent(Vector2 position);
	RenderComponent(std:: string filename);

	virtual ~RenderComponent() override {};
	// Inherited via IComponent
	virtual void start() override {};
	virtual void updateComponent() override {};
	virtual void render() override {};
	virtual int RenderOrder() =0;
	virtual RenderComponent* clone() const = 0;

protected:
	std::string fileName;
	Vector2 centerScreen;
	Vector2 offset;

	
};

