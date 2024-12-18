#pragma once
#include "Components/Transform.h"
#include<unordered_map>
#include <string>

class SpriteRenderer;
class Entity
{
public:
	Entity(int ID);
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
	void SetScale(const Vector2& scale);
	
	//Getters
	bool IsEnabled() const;
	int GetID() const;
	std::string GetTag() const;

	Vector3 GetPosition();

	IComponent* GetComponent(ComponentType type);
	std::vector<IComponent*> GetComponents() const;


	Transform transform;
private:

	bool isActive = true;
	int enitityID;

	std::string m_Tag = "Unkown";
	std::unordered_map<ComponentType,IComponent*> listOfComponents;

	SpriteRenderer* objectSprite;
};

