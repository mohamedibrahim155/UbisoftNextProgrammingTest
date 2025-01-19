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

	
	
	Entity(EntityID ID);
	Entity(const Entity& otherEntity , EntityID ID);
	virtual ~Entity();


	void addComponent(eComponentType type,IComponent* component);
	void addComponent(IComponent* component);
	void addComponents(std::vector<IComponent*> components);
	bool removeComponent(eComponentType type);
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

	CEvent<> OnDestroyed;
	CEvent<IComponent*> OnComponentAdded;

private:

	bool m_isActive = true;
	EntityID m_entityID;

	std::string m_tag = "Unkown";
	std::unordered_map<eComponentType,IComponent*> m_listOfComponents;



};

