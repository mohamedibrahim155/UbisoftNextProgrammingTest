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


	void addComponent(ComponentType type,IComponent* component);
	void addComponent(IComponent* component);
	void addComponents(std::vector<IComponent*> components);
	bool removeComponent(ComponentType type);
	void Destroy();
	void cleanUps();

	//Setters
	void setActive(bool isActive);
	void setTag(const std::string& tag);
	void setID(int ID);
	void setPosition(const Vector3& position);
	void setRotation(const float& rotationY);
	void setScale(const Vector2& scale);
	
	//Getters
	bool IsActive() const;
	int getID() const;
	std::string getTag() const;

	Vector3 getPosition();

	IComponent* GetComponent(ComponentType type);
	std::vector<IComponent*> GetComponents() const;


	Transform transform;
	SpriteRenderer* m_sprite;

	EntityManager* m_entityManager;


	bool isDestroyed = false;

	CEvent<> OnDestroyed;
	CEvent<IComponent*> OnComponentAdded;

private:

	bool m_isActive = true;
	EntityID m_entityID;

	std::string m_tag = "Unkown";
	std::unordered_map<ComponentType,IComponent*> m_listOfComponents;



};

