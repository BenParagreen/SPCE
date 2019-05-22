#pragma once

//Project Includes
#include "Framework/MovingObject.h"

class EnemyBullet
	: public MovingObject
{
public:
	EnemyBullet();

	void Update(sf::Time _frameTime);

	void Fire(sf::Vector2f _target);

	//Overriding Methods
	void Collide(GameObject& _collider);
}; 
