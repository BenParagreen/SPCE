#include "AbilityHolder.h"
#include "Framework/AssetManager.h"

AbilityHolder::AbilityHolder()
	: SpriteObject() // Initialise parent class
	, m_player(nullptr)
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/NoAbility.png"));
}

void AbilityHolder::Update(sf::Time _frametime)
{
	if (m_player != nullptr)
	{
		bool speedup = m_player->GetAbility();
		if (speedup == true)
		    m_sprite.setTexture(AssetManager::GetTexture("graphics/SpeedUpStored.png"));
	}
}


void AbilityHolder::SetPlayer(Player* _player)
{
	m_player = _player;
}