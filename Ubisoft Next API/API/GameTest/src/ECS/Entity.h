///////////////////////////////////////////////////////////////////////////////
// Filename: Entity.h
// Entity holds the maps of components and Unique ID's
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Components/Transform.h"
#include<unordered_map>
#include <string>
#include "../src/Events/Event.h"
class SpriteRenderer;
class EntityManager;
using EntityID = int;
class Entity
{
public:

	
	// creates from entity manager
	Entity(EntityID ID);

	// copy entity from other
	Entity(const Entity& otherEntity , EntityID ID);
	virtual ~Entity();

	// add components to map
	void addComponent(eComponentType type,IComponent* component);
	void addComponent(IComponent* component);
	void addComponents(std::vector<IComponent*> components);
	bool removeComponent(eComponentType type);

	//cleans the entity
	void Destroy();
	void cleanUps();

	void copyComponents(const Entity& otherEntity);

	//Setters
	void setActive(bool isActive);
	void setTag(const std::string& tag);
	void setID(int ID);
	void setPosition(const Vector3& position, const Vector3& cameraPosition);
	void setRotation(const float& rotationY);
	void setScale(const Vector2& scale);
	
	//Getters
	bool IsActive() const;
	int getID() const;
	std::string getTag() const;

	Vector3 getPosition();

	IComponent* getComponent(eComponentType type);
	std::vector<IComponent*> getComponents() const;


	Transform transform;
	SpriteRenderer* m_sprite;

	bool isDestroyed = false;
	bool dontDestoryOnLoad = false;

	//event triggered when entity dynamically destroyed
	CEvent<> OnDestroyed;

	//event when component added to notify the relavant system
	CEvent<IComponent*> OnComponentAdded;

private:

	bool m_isActive = true;

	// unique Entity ID
	EntityID m_entityID;

	std::string m_tag = "Unkown";

	// maps holds the type of component
	std::unordered_map<eComponentType,IComponent*> m_listOfComponents;



};

