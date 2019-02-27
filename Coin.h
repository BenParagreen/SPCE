#pragma once

//Project Includes
#include "Pickup.h"

class Coin : public Pickup
{
public:
	Coin();
private:
	virtual void onPickup(Player& _player);
};

