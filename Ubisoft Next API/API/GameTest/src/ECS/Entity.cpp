#include "stdafx.h"
#include "Entity.h"

Entity::~Entity()
{
	CleanUps();
}

void Entity::AddComponent(ComponentType type,IComponent* component)
{
	if (type == ComponentType::TRANSFORM_COMPONENT)
	{
		this->transform = *(static_cast<Transform*>(component));
	}

	component->SetEntity(this);
	listOfComponents[type] =  component;

}

void Entity::AddComponent(IComponent* component)
{
	if (component->GetComponentType() == ComponentType::TRANSFORM_COMPONENT)
	{
		this->transform = *(static_cast<Transform*>(component));
	}

	component->SetEntity(this);
	listOfComponents[component->GetComponentType()] = component;
}

void Entity::AddComponents(std::vector<IComponent*> components)
{
	for (IComponent* component :  components)
	{
		AddComponent(component->GetComponentType(), component);
	}
}

bool Entity::RemoveComponent(ComponentType type)
{
	std::unordered_map<ComponentType, IComponent*> ::iterator it = listOfComponents.find(type);
	
	if (it != listOfComponents.end())
	{
		listOfComponents.erase(type);
		return true;
	}

	return false;

}



std::vector<IComponent*> Entity::GetComponents() const
{
	std::vector<IComponent*> components;

	for (std::pair<ComponentType, IComponent*> item : listOfComponents)
	{
		components.push_back(item.second);
	}
	return components;
}

IComponent* Entity::GetComponent(ComponentType type)
{
	
	return listOfComponents[type];
}

void Entity::CleanUps()
{
	

	for (std::pair<ComponentType, IComponent*> item : listOfComponents)
	{
		if (item.second)
		{
			delete item.second;
		}
	}

	listOfComponents.clear();
}
