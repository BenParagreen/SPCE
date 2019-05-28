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
		//check that slow mo is ready on the player
		bool slowmoready = m_player->GetSlowMoReady();

		// If  it is ready change the sprite to indicate so
		if (slowmoready == true)
			m_sprite.setTexture(AssetManager::GetTexture("graphics/SlowMoReady.png"));
		// If it isn't ready set sprite to show that it isn't ready
		if (slowmoready == false)
			m_sprite.setTexture(AssetManager::GetTexture("graphics/NoSlowMo.png"));
	}
}

void SlowMoSignal::SetPlayer(Player* _player)
{
	m_player = _player;
}