//Project Includes
#include "SpeedUp.h"
#include "Framework/AssetManager.h"

// Constants
#define POS_Y_MIN 100
#define POS_Y_MAX 900

#define VELOCITY -100


SpeedUp::SpeedUp()
	: Pickup()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/SpeedUp.png"));
	m_velocity.x = VELOCITY;
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

void SpeedUp::Spawn()
{
	// Choose a random y position
	sf::Vector2f position;
	position.y = rand() % (POS_Y_MAX - POS_Y_MIN) + POS_Y_MIN;
	position.x = 1800.0f;

	SetPosition(position);
}