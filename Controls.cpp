// Project Includes
#include "Controls.h"
#include "Framework/AssetManager.h"

Controls::Controls()
	: TextObject() // Initialise parent class
{
	m_Text.setFont(AssetManager::GetFont("fonts/mainFont.ttf"));
	m_Text.setString("Controls:  WASD = move    G = Fire    H = Slow Motion Abilty   J = Pickup Ability   ");


	sf::Vector2f position;
	position.y = 1000;
	position.x = 110;
	SetPosition(position);

}

