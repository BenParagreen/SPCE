#pragma once

//Project Includes
#include "Framework/TextObject.h"
#include "Player.h"

class Score : public TextObject
{
public:
	Score();

	// Overriding Methods
	virtual void Update(sf::Time _frametime);

	// Public Score Methods
	void SetPlayer(Player* _player);

private:
	Player* m_player;
};