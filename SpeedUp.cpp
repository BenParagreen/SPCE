//Project Includes
#include "SpeedUp.h"
#include "Framework/AssetManager.h"

Key::Key()
	: Pickup()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/SpeedUp.png"));
	// TEMP KEY POSITION
}

void Key::onPickup(Player& _player)
{
	_player.HasKey(true);
}