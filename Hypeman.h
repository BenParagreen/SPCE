
#pragma once

//Project Includes
#include "Framework/TextObject.h"
#include "Player.h"

class Hypeman : public TextObject
{
public:
	Hypeman();

	// Overriding Methods
	virtual void Update(sf::Time _frametime);

	// Public Score Methods
	void SetLevel(Level* _playthrough);

private:
	Level* m_level;
};