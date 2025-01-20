#pragma once
#include "Enums/EComponentType.h"



class Entity;

class IComponent
{
public:

	IComponent(eComponentType type);
	virtual ~IComponent() = default;
	
	virtual void start() = 0;
	virtual void updateComponent() = 0;
	virtual void render(bool isDebugRender = false) = 0;
	virtual void cleanUp() = 0;
	virtual IComponent* clone() const = 0;

	void setEntity(Entity* entity);
	void setEnabled(bool state);
	void setUI(bool isUI);

	bool IsUI() const { return m_isUI; }
	eComponentType getComponentType();
	Entity* getEntity() const;


	int componentID;
	bool m_isEnabled = true;
	bool m_isStartInvoked = false;
	




protected:
	bool m_isUI = false;
	Entity* gameObject;
	Vector3 m_debugColor{ 1,0,0 };
};

