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


	void AddComponent(ComponentType type,IComponent* component);
	void AddComponent(IComponent* component);
	void AddComponents(std::vector<IComponent*> components);
	bool RemoveComponent(ComponentType type);
	void Destroy();
	void CleanUps();

	//Setters
	void SetActive(bool isActive);
	void SetTag(const std::string& tag);
	void SetID(int ID);
	void SetPosition(const Vector3& position);
	void SetRotation(const float& rotationY);
	void SetScale(const Vector2& scale);
	
	//Getters
	bool IsActive() const;
	int GetID() const;
	std::string GetTag() const;

	Vector3 GetPosition();

	IComponent* GetComponent(ComponentType type);
	std::vector<IComponent*> GetComponents() const;


	Transform transform;
	SpriteRenderer* m_sprite;

	EntityManager* manager;


	bool isDestroyed = false;

	CEvent<> OnDestroyed;

private:

	bool isActive = true;
	EntityID enitityID;

	std::string tag = "Unkown";
	std::unordered_map<ComponentType,IComponent*> listOfComponents;



};

