///////////////////////////////////////////////////////////////////////////////
// Filename: IComponent.h
// interface to create different types of components
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Enums/EComponentType.h"

///--------------------------------------------------------------------------------
// every component have Entity aka gameobject to know which entity that this 
// component is attached.
///--------------------------------------------------------------------------------

class Entity;

class IComponent
{
public:

	IComponent(eComponentType type);
	virtual ~IComponent() = default;
	
	//Inits component
	virtual void start() = 0;

	//updates component everyframe
	virtual void updateComponent() = 0;

	//render component
	virtual void render(bool isDebugRender = false) = 0;

	// cleans the component
	virtual void cleanUp() = 0;

	// creates a copy component
	virtual IComponent* clone() const = 0;

	//sets gameObject
	void setEntity(Entity* entity);

	//sets if component is Active
	void setEnabled(bool state);

	// sets if component is UI
	void setUI(bool isUI);

	//Getters
	bool IsUI() const { return m_isUI; }
	eComponentType getComponentType();
	Entity* getEntity() const;


	int componentID;
	bool m_isEnabled = true;

	//first frame invoke
	bool m_isStartInvoked = false;
	




protected:
	bool m_isUI = false;
	Entity* gameObject;
	Vector3 m_debugColor{ 1,0,0 };
};

