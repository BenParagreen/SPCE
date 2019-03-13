#pragma once

//Project Includes
#include "Pickup.h"

class SpeedUp : public Pickup
{
public:
    SpeedUp();
	void Update(sf::Time _frameTime);

	void Spawn();

private:
	virtual void onPickup(Player& _player);
};

