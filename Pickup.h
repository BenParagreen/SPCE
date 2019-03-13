#pragma once

//Project includes
#include "Framework/SpriteObject.h"
#include "Player.h"

class Pickup : public MovingObject
{
public:
	Pickup();

	//Overriding method
	void Collide(GameObject& _collider);

private:
	virtual void onPickup(Player& _player);

};