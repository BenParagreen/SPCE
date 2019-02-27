//Project Includes
#include "Coin.h"
#include "Framework/AssetManager.h"

Coin::Coin()
	: Pickup()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Coin.png"));
	// TEMP COIN POSITION
}

void Coin::onPickup(Player& _player)
{
	_player.ChangeScore(1);
}