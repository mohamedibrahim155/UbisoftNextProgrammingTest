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
	
	virtual void start() = 0;
	virtual void updateComponent() = 0;
	virtual void render() = 0;
	virtual IComponent* clone() const = 0;

	void setEntity(Entity* entity);
	void setEnabled(bool state);
	void setUI(bool isUI);

	bool IsUI() const { return isUI; }
	ComponentType getComponentType();
	Entity* getEntity() const;


	int componentID;
	bool isComponentEnabled = true;
	bool isStartInvoked = false;
	




protected:
	Entity* gameObject;
	bool isUI = false;

	Vector3 debugColor{ 0,1,0 };
};

