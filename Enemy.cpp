//Library Includes
#include "Enemy.h"
#include "Framework/AssetManager.h"

Enemy::Enemy()
	: MovingObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/EnemyShip.png"));
	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;
}
