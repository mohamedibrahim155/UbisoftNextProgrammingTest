#pragma once
#include "Components/Transform.h"
#include<unordered_map>
#include <string>

class Entity
{
public:
	Entity() = default;
	virtual ~Entity();


	void AddComponent(ComponentType type,IComponent* component);
	void AddComponent(IComponent* component);
	void AddComponents(std::vector<IComponent*> components);
	void CleanUps();
	bool RemoveComponent(ComponentType type);
	
	std::vector<IComponent*> GetComponents() const;
	IComponent* GetComponent(ComponentType type);

	//virtual void UpdateComponents() = 0;

	Transform transform;
	int enitityID;
	bool isActive = true;
	std::string m_Tag =  "Unkown";

private:
	std::unordered_map<ComponentType,IComponent*> listOfComponents;
};

