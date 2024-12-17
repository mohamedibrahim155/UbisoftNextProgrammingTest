#pragma once
#include "../Component.h"
#include "../App/SimpleSprite.h"

class Entity;


class RenderComponent : public IComponent
{
public:
	RenderComponent(std:: string filename);

	~RenderComponent() override;
	// Inherited via IComponent
	void Initialise() override;
	void UpdateComponent() override;
	void Render() override;

	
	CSimpleSprite* GetSprite();

private:

	CSimpleSprite* sprite;
	std::string fileName;

	



};

