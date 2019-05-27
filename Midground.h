#pragma once

//Project Includes
#include "Framework/MovingObject.h"

class Midground
	: public MovingObject
{
public:
	Midground();

	void Spawn();

	void Update(sf::Time _frameTime);


private:

	static float s_furthestPoint;

	sf::Vector2f m_spawnposition;
	sf::Vector2f m_spriteposition;
	sf::Vector2f m_falloffpoint;
	sf::Vector2f currentPosition;
}; 
