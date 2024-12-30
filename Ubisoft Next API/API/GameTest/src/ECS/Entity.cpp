#include "stdafx.h"
#include "Entity.h"
#include "Components/SpriteRenderer.h"
#include"../src/ECS/EntityManager.h"
#include "Components/Collider/Collider.h"
Entity::Entity(EntityID ID) : enitityID(ID)
{
	m_sprite = nullptr;

	AddComponent(new Transform());
}

Entity::Entity(const Entity& otherEntity, EntityID ID)
{

	auto components = otherEntity.GetComponents();
	for (IComponent* component: components)
	{
		AddComponent(component->GetComponentType(), component->Clone());
	}
	
	isActive = otherEntity.isActive;
	tag = otherEntity.tag + "_copy";
	enitityID = ID;
	if (otherEntity.manager)
	{
		manager = otherEntity.manager;
		
	}

}

Entity::~Entity()
{
	CleanUps();
}

void Entity::AddComponent(ComponentType type,IComponent* component)
{
	component->SetEntity(this);
	listOfComponents[type] = component;

	//Intial References
	switch (component->GetComponentType())
	{
	case ComponentType::TRANSFORM_COMPONENT:
		transform = *(dynamic_cast<Transform*>(component));
		break;

	case ComponentType::RENDER_COMPONENT:
		m_sprite = dynamic_cast<SpriteRenderer*>(component);
		break;

	case ComponentType::COLLIDER_COMPONENT:

		Collider* collider = dynamic_cast<Collider*>(component);

		collider->Init();
		break;
	}

	

}

void Entity::AddComponent(IComponent* component)
{

	component->SetEntity(this);
	listOfComponents[component->GetComponentType()] = component;


	//Intial References
	switch (component->GetComponentType())
	{
	case ComponentType::TRANSFORM_COMPONENT:
		transform = *(dynamic_cast<Transform*>(component));
		break;

	case ComponentType::RENDER_COMPONENT:
		m_sprite = dynamic_cast<SpriteRenderer*>(component);
		break;

	case ComponentType::COLLIDER_COMPONENT:

		Collider* collider = dynamic_cast<Collider*>(component);

		//Calculates the colliders bounds based on sprite width and height
		collider->Init();
		break;
	}
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

void Entity::Destroy()
{
	if (isDestroyed) return;

	OnDestroyed.Invoke();
	SetActive(false);
	isDestroyed = true;
	CleanUps();
	if (manager)
	{
		manager->RemoveEntity(enitityID);
	}
	

	//delete this;
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

std::string Entity::GetTag() const
{
	return tag;
}

Vector3 Entity::GetPosition() 
{
	float x, y;

	m_sprite->GetSprite()->GetPosition(x, y);

	Vector3 position = Vector3(x, y, 0);
	transform.position = position;

	return transform.position;
}

bool Entity::IsActive() const
{
	return isActive;
}

int Entity::GetID() const
{
	return enitityID;
}


void Entity::SetActive(bool isActive)
{
	this->isActive = isActive;

	
	std::vector<IComponent*> componentList = GetComponents();

	for (IComponent* component : componentList)
	{
		if (component->isComponentEnabled)
		{
			component->SetEnabled(isActive);
		}
	}

}

void Entity::SetTag(const std::string& tag)
{
	this->tag = tag;
}

void Entity::SetID(int ID)
{
	this->enitityID = ID;
}

void Entity::SetPosition(const Vector3& position)
{
	transform.position = position;

	if (m_sprite)
	{
		m_sprite->SetPosition(transform.position);
	}

}

void Entity::SetRotation(const float& rotationY)
{
	transform.rotation = rotationY;

	if (m_sprite)
	{
		m_sprite->SetRotation(transform.rotation);
	}

}

void Entity::SetScale(const Vector2& scale)
{
	this->transform.scale = scale;

	if (m_sprite)
	{
		m_sprite->SetScale(scale);
	}
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
