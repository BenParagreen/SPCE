#pragma once

//Project Include
#include "Framework/MovingObject.h"

class Enemy : public MovingObject
{
public:
	Enemy();

	void Update(sf::Time _frameTime);
	void Spawn();

	//Override
	virtual void Collide(GameObject& _collider);
};