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
	void SetGame(Level* _player);

private:
	Level* m_level;
};