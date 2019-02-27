//Project Includes
#include "Key.h"
#include "Framework/AssetManager.h"

Key::Key()
	: Pickup()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Key.png"));
	// TEMP KEY POSITION
}

void Key::onPickup(Player& _player)
{
	_player.HasKey(true);
}