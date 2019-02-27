#pragma once

//Project Includes
#include "Pickup.h"

class Key : public Pickup
{
public:
	Key();
private:
	virtual void onPickup(Player& _player);
};

