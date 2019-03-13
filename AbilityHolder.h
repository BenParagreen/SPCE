#pragma once

//Project Include
#include "Framework/SpriteObject.h"
#include "Player.h"

class AbilityHolder : public SpriteObject
{
public:
	AbilityHolder();

	// Overriding Methods
	void Update(sf::Time _frametime);

	// Public Collected Methods
	void SetPlayer(Player* _player);

	

private:
	Player* m_player;
};