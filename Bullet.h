#pragma once

//Project Includes
#include "Framework/MovingObject.h"

class Bullet
	: public MovingObject
{
public:
	Bullet();

	void Update(sf::Time _frameTime);

	void Fire(sf::Vector2f _target);

	//Overriding Methods
    void Collide(GameObject& _collider);
};