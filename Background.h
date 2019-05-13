#pragma once

//Project Includes
#include "Framework/MovingObject.h"

class Background
	: public MovingObject
{
public:
	Background();

	void Spawn();

	void Update(sf::Time _frameTime);


private:
    // Background shared data
    static float s_furthestPoint;
	float m_fallOffPoint;


	sf::Vector2f m_oldvelocity;
};