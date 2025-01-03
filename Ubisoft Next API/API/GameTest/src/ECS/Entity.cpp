#include "stdafx.h"
#include "Entity.h"
#include "Components/Renders/SpriteRenderer.h"
#include"../src/ECS/EntityManager.h"
#include "Components/Collider/Collider.h"
Entity::Entity(EntityID ID) : m_entityID(ID)
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
	
	m_isActive = otherEntity.m_isActive;
	m_tag = otherEntity.m_tag + "_copy";
	m_entityID = ID;
	if (otherEntity.m_entityManager)
	{
		m_entityManager = otherEntity.m_entityManager;
		
	}

}

Entity::~Entity()
{
	cleanUps();
}

void Entity::addComponent(ComponentType type,IComponent* component)
{
	component->setEntity(this);
	m_listOfComponents[type] = component;

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

	OnComponentAdded.Invoke(component);

}

void Entity::addComponent(IComponent* component)
{

	component->setEntity(this);
	m_listOfComponents[component->getComponentType()] = component;


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

	//Triggers component ADDED
	OnComponentAdded.Invoke(component);
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
	std::unordered_map<ComponentType, IComponent*> ::iterator it = m_listOfComponents.find(type);
	
	if (it != m_listOfComponents.end())
	{
		m_listOfComponents.erase(type);

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
	if (m_entityManager)
	{
		m_entityManager->removeEntity(m_entityID);
	}
	

	//delete this;
}



std::vector<IComponent*> Entity::GetComponents() const
{
	std::vector<IComponent*> components;

	for (std::pair<ComponentType, IComponent*> item : m_listOfComponents)
	{
		components.push_back(item.second);
	}
	return components;
}

IComponent* Entity::GetComponent(ComponentType type)
{
	return m_listOfComponents[type];
}

std::string Entity::getTag() const
{
	return m_tag;
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
	return m_isActive;
}

int Entity::getID() const
{
	return m_entityID;
}


void Entity::setActive(bool isActive)
{
	this->m_isActive = isActive;

	
	std::vector<IComponent*> componentList = GetComponents();

	for (IComponent* component : componentList)
	{
		if (!component) continue;

		if (component->m_isEnabled)
		{
			component->setEnabled(isActive);
		}
	}

}

void Entity::setTag(const std::string& tag)
{
	this->m_tag = tag;
}

void Entity::setID(int ID)
{
	this->m_entityID = ID;
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
	for (std::pair<ComponentType, IComponent*> item : m_listOfComponents)
	{
		if (item.second)
		{
			delete item.second;
		}
	}
	
	m_listOfComponents.clear();

}
