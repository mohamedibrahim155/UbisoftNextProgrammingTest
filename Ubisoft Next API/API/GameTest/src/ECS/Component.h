#pragma once


enum class ComponentType
{
	UNKOWN_COMPONENT = -1,

	TRANSFORM_COMPONENT = 1,
	SCRIPT_COMPONENT = 2,
	PHYSICS_COMPONENT = 3,
	COLLIDER_COMPONENT = 4,
	RENDER_COMPONENT =5,
};

class Entity;

class IComponent
{
public:

	IComponent(ComponentType type);
	virtual ~IComponent() = default;
	
	virtual void Start() = 0;
	virtual void UpdateComponent() = 0;
	virtual void Render() = 0;

	void SetEntity(Entity* entity);
	void SetEnabled(bool state);
	ComponentType GetComponentType();
	Entity* GetEntity() const;

	int componentID;
	bool isComponentEnabled = true;
	bool isStartInvoked = false;


protected:
	Entity* entityRef;
};

