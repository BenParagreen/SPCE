#pragma once

//Project Include
#include "Framework/SpriteObject.h"
#include "Player.h"

class Exit : public SpriteObject
{
public:
	Exit();

	// Overriding Methods
	void Update(sf::Time _frametime);
    void Collide(GameObject& _collider);

	// Public Collected Methods
	void SetPlayer(Player* _player);

	

private:
	Player* m_player;
};