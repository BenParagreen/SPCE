#pragma once

//Library Includes
#include <SFML/Graphics.hpp>

class GameObject
{
public:

	GameObject();

//These are very simple or early functions
//That can be overriden in derived classes
	virtual void Draw(sf::RenderTarget& _target);
	virtual void Update(sf::Time _frametime);
	virtual sf::FloatRect GetBounds();
	virtual void Collide(GameObject& _collider);
	virtual void SetPosition(sf::Vector2f _position);
	virtual void SetPosition(float _x, float _y);
	virtual sf::Vector2f GetPosition();
	bool isActive();
	bool SlowMo(bool _slowed);

protected:
	bool m_active;
	bool m_slowed;
};