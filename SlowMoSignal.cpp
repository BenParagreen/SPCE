#include "SlowMoSignal.h"
#include "Framework/AssetManager.h"

SlowMoSignal::SlowMoSignal()
	: SpriteObject() // Initialise parent class
	, m_player(nullptr)
{
	//Set texture to empty
	m_sprite.setTexture(AssetManager::GetTexture("graphics/NoSlowMo.png"));
}

void SlowMoSignal::Update(sf::Time _frametime)
{
	// If the player is active
	if (m_player != nullptr)
	{
		//check that the player picked up speedup
		bool speedup = m_player->GetSlowMoReady();

		// If pickup was speedup change the stored sprite to show speed up 
		if (speedup == true)
			m_sprite.setTexture(AssetManager::GetTexture("graphics/SlowMoReady.png"));

		if (speedup == false)
			m_sprite.setTexture(AssetManager::GetTexture("graphics/NoSlowMo.png"));
	}
}


void SlowMoSignal::SetPlayer(Player* _player)
{
	m_player = _player;
}