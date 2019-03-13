//Library Includes
#include "Enemy.h"
#include "Framework/AssetManager.h"

Enemy::Enemy()
	: MovingObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/EnemyShip.png"));
	m_velocity.x = -50.0f;
	m_velocity.y = 0.0f;
}

void Enemy::Update(sf::Time _frameTime)
{
	//Call the update function manually on the parent class
	// this will actually move the character
	MovingObject::Update(_frameTime);

}
