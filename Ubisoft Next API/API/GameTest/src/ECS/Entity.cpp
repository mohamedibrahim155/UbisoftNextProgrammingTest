#include "stdafx.h"
#include "Entity.h"
#include "Components/Renders/SpriteRenderer.h"
#include"../src/ECS/EntityManager.h"
#include "Components/Collider/Collider.h"
#include "../src/ECS/Components/UI/ButtonRenderer.h"
Entity::Entity(EntityID ID) : m_entityID(ID)
{
	m_sprite = nullptr;

	addComponent(new Transform());
}

Entity::Entity(const Entity& otherEntity, EntityID ID)
{

	m_entityID = ID;
	
	copyComponents(otherEntity);
	
	m_isActive = otherEntity.m_isActive;
	m_tag = otherEntity.m_tag + std::to_string(ID) + "_copy";

	

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

	OnComponentAdded.Invoke(m_listOfComponents[type]);

}

void Entity::addComponent(IComponent* component)
{

	component->setEntity(this);
	ComponentType type = component->getComponentType();
	
	m_listOfComponents[type] = component;

	//Intial References
	switch (type)
	{
	case ComponentType::TRANSFORM_COMPONENT:
		transform = *(dynamic_cast<Transform*>(component));
		break;

	case ComponentType::RENDER_COMPONENT:
		if (!m_sprite)
		{
			m_sprite = dynamic_cast<SpriteRenderer*>(component);
		}
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

	setActive(false);
	isDestroyed = true;
	cleanUps();
	OnDestroyed.Invoke();
}




std::vector<IComponent*> Entity::getComponents() const
{
	std::vector<IComponent*> components;

	for (std::pair<ComponentType, IComponent*> item : m_listOfComponents)
	{
		if (item.second)
		{
			components.push_back(item.second);
		}
		
	}
	return components;
}

IComponent* Entity::getComponent(ComponentType type)
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
	if (!m_sprite)
	{
		return transform.position;
	}
	m_sprite->getSprite()->GetPosition(x, y);

	Vector3 position = Vector3(x, y, 0);
	transform.position = position;

	return position;
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

	
	std::vector<IComponent*> componentList = getComponents();

	for (IComponent* component : componentList)
	{
		if (!component) continue;

		//if (component->m_isEnabled )
		
		component->setEnabled(isActive);
		
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

/// <summary>
/// Sets position of Sprite
/// </summary>
/// <param name="scale"> rotation degree</param>
void Entity::setPosition(const Vector3& position, const Vector3& cameraPosition)
{

	// Update the sprite's position for rendering
		transform.position = position;
		transform.localPosition = position - cameraPosition;

	if (m_sprite)
	{
		m_sprite->setPosition(position, cameraPosition);
	}
}
/// <summary>
/// Sets rotation of Sprite
/// </summary>
/// <param name="scale"> rotation degree</param>
void Entity::setRotation(const float& rotationY)
{
	transform.rotation = rotationY;

	if (m_sprite)
	{
		m_sprite->setRotation(transform.rotation);
	}

}
/// <summary>
/// Set scale of sprite
/// </summary>
/// <param name="scale"> size of scale</param>
void Entity::setScale(const Vector2& scale)
{
	transform.scale = scale;

	if (m_sprite)
	{
		m_sprite->setScale(scale);
	}
}



void Entity::cleanUps()
{
	// Cleaning Components attached to this gameobject
	for (std::pair<ComponentType, IComponent*> item : m_listOfComponents)
	{
		if (item.second)
		{
			item.second->cleanUp();

			if (item.second->m_isStartInvoked)
			{
				item.second->m_isStartInvoked = false;
			}

			delete item.second;
		}
	}
	
	m_listOfComponents.clear();

}

void Entity::copyComponents(const Entity& otherEntity)
{
	auto components = otherEntity.getComponents();
	for (IComponent* component : components)
	{
		addComponent(component->getComponentType(), component->clone());
	}
}
