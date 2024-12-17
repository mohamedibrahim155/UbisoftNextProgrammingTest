#pragma once
#include "Entity.h"
class ISystem   
{
public:

	ISystem() = default;

	virtual ~ISystem() = default;
	virtual void Start()=0;
	virtual void Update(std::vector<Entity*> entities,float deltaTime) = 0;
	virtual void Render(std::vector<Entity*> entities) =0;
	virtual void Cleanups() =0;

};

