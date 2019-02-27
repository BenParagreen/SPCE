#pragma once

//Project Include
#include "SpriteObject.h"

class MovingObject : public SpriteObject
{
public:
	MovingObject();

	//Overriding Methods
	void Update(sf::Time _frameTime);

protected:

	sf::Vector2f m_velocity;
	sf::Vector2f m_previousPosition;
};
