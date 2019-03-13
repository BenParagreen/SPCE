//Project includes 
#include "Pickup.h"
#include "Player.h"

Pickup::Pickup()
	: MovingObject()
{

}

void Pickup::Collide(GameObject& _collider)
{
	// Only do something if colliding with player

	// Take the generic reference to a Game object passed in
	//we get the address for that Game Object
	//we attempt to treat that address as if it is for a player
	//if successful. it IS a player and the address is stored in castPlayer
	//if not successful, it is NOT a player and nullptr is stored in castPlayer
	Player* castPlayer = dynamic_cast<Player*>(&_collider);

	if (castPlayer != nullptr)
	{
		// Do something based on type of pickup
		onPickup(*castPlayer);
	    // Dissapear
		m_active = false;
	}


}

void Pickup::onPickup(Player& _player)
{
	//Do nothing
}