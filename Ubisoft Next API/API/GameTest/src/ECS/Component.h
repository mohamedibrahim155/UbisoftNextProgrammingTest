#pragma once


enum class ComponentType
{
	UNKOWN_COMPONENT =-1,
	TRANSFORM_COMPONENT = 1,

	RENDER_COMPONENT =2,


};

class Entity;

class IComponent
{
public:

	IComponent(ComponentType type);
	virtual ~IComponent() = default;
	
	virtual void Initialise() = 0;
	virtual void UpdateComponent() = 0;
	virtual void Render() = 0;
	ComponentType GetComponentType();

	void SetEntity(Entity* entity);
	void SetEnabled(bool state);
	int componentID;
	bool isComponentEnabled = true;


protected:

	Entity* entityRef;
};

