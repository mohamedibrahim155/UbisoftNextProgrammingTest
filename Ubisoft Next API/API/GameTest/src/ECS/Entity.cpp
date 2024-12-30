#include "stdafx.h"
#include "Entity.h"
#include "Components/Renders/SpriteRenderer.h"
#include"../src/ECS/EntityManager.h"
#include "Components/Collider/Collider.h"
Entity::Entity(EntityID ID) : enitityID(ID)
{
	m_sprite = nullptr;

	addComponent(new Transform());
}

Entity::Entity(const Entity& otherEntity, EntityID ID)
{

	auto components = otherEntity.GetComponents();
	for (IComponent* component: components)
	{
		addComponent(component->getComponentType(), component->clone());
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
	cleanUps();
}

void Entity::addComponent(ComponentType type,IComponent* component)
{
	component->setEntity(this);
	listOfComponents[type] = component;

	//Intial References
	switch (component->getComponentType())
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

void Entity::addComponent(IComponent* component)
{

	component->setEntity(this);
	listOfComponents[component->getComponentType()] = component;


	//Intial References
	switch (component->getComponentType())
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

void Entity::addComponents(std::vector<IComponent*> components)
{
	for (IComponent* component :  components)
	{
		addComponent(component->getComponentType(), component);
	}
}

bool Entity::removeComponent(ComponentType type)
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
	setActive(false);
	isDestroyed = true;
	cleanUps();
	if (manager)
	{
		manager->removeEntity(enitityID);
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

std::string Entity::getTag() const
{
	return tag;
}

Vector3 Entity::getPosition() 
{
	float x, y;

	m_sprite->getSprite()->GetPosition(x, y);

	Vector3 position = Vector3(x, y, 0);
	transform.position = position;

	return transform.position;
}

bool Entity::IsActive() const
{
	return isActive;
}

int Entity::getID() const
{
	return enitityID;
}


void Entity::setActive(bool isActive)
{
	this->isActive = isActive;

	
	std::vector<IComponent*> componentList = GetComponents();

	for (IComponent* component : componentList)
	{
		if (component->isComponentEnabled)
		{
			component->setEnabled(isActive);
		}
	}

}

void Entity::setTag(const std::string& tag)
{
	this->tag = tag;
}

void Entity::setID(int ID)
{
	this->enitityID = ID;
}

void Entity::setPosition(const Vector3& position)
{
	transform.position = position;

	if (m_sprite)
	{
		m_sprite->setPosition(transform.position);
	}

}

void Entity::setRotation(const float& rotationY)
{
	transform.rotation = rotationY;

	if (m_sprite)
	{
		m_sprite->setRotation(transform.rotation);
	}

}

void Entity::setScale(const Vector2& scale)
{
	this->transform.scale = scale;

	if (m_sprite)
	{
		m_sprite->setScale(scale);
	}
}



void Entity::cleanUps()
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
