//Project Includes
#include "SpeedUp.h"
#include "Framework/AssetManager.h"

SpeedUp::SpeedUp()
	: Pickup()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/SpeedUp.png"));
	m_velocity.x = -40.0f;
	m_velocity.y = 0.0f;
}

void SpeedUp::Update(sf::Time _frameTime)
{
	//Call the update function manually on the parent class
	// this will actually move the character
	MovingObject::Update(_frameTime);

}

void SpeedUp::onPickup(Player& _player)
{
	_player.HasAbility(true);
}