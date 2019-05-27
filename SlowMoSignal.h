#pragma once

//Project Include
#include "Framework/SpriteObject.h"
#include "Player.h"

class SlowMoSignal : public SpriteObject
{
public:
	SlowMoSignal();

	// Overriding Methods
	void Update(sf::Time _frametime);

	// Public Collected Methods
	void SetPlayer(Player* _player);

private:
	Player* m_player;
};