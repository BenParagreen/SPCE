//Project Includes 
#include "GameObject.h"

GameObject::GameObject()
	:m_active(true)
	,m_slowed(false)
{

}

void GameObject::Draw(sf::RenderTarget& _target)
{

}

void GameObject::Update(sf::Time _frameTime)
{

}

sf::FloatRect GameObject::GetBounds()
{
	return sf::FloatRect();
}

void GameObject::Collide(GameObject& _collider)
{

}

void GameObject::SetPosition(sf::Vector2f _position)
{

}

void GameObject::SetPosition(float _x, float _y)
{

}


bool GameObject::isActive()
{
	return m_active;
}

bool GameObject::SlowMo(bool _slowed)
{
	m_slowed = _slowed;
	return m_slowed;
}

sf::Vector2f GameObject :: GetPosition()
{
	return sf::Vector2f();
}
