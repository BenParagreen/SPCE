#include "Exit.h"
#include "Framework/AssetManager.h"

Exit::Exit()
	: SpriteObject() // Initialise parent class
	, m_player(nullptr)
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorClosed.png"));
}

void Exit::Update(sf::Time _frametime)
{
	if (m_player != nullptr)
	{
		bool key = m_player->GetKey();
		if (key == true)
		    m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorOpen.png"));
	}
}

void Exit::Collide(GameObject& _collider)
{
	// Only do something if colliding with player

	Player* castPlayer = dynamic_cast<Player*>(&_collider);

	if (castPlayer != nullptr)
	{
		//Does player have key
		if (castPlayer->GetKey())
		{
			// Touched by the player
			// Load Next Level
			castPlayer->AdvanceLevel();
		}
	}
}

void Exit::SetPlayer(Player* _player)
{
	m_player = _player;
}