#include "AbilityHolder.h"
#include "Framework/AssetManager.h"

AbilityHolder::AbilityHolder()
	: SpriteObject() // Initialise parent class
	, m_player(nullptr)
{
	//Set texture to empty
	m_sprite.setTexture(AssetManager::GetTexture("graphics/NoAbility.png"));
}

void AbilityHolder::Update(sf::Time _frametime)
{
	// If the player is active
	if (m_player != nullptr)
	{

		//check that the player picked up speedup
		bool speedup = m_player->GetAbility();
		// If pickup was speedup change the stored sprite to show speed up 
		if (speedup == true)
		    m_sprite.setTexture(AssetManager::GetTexture("graphics/SpeedUpStored.png"));
	}
}


void AbilityHolder::SetPlayer(Player* _player)
{
	m_player = _player;
}