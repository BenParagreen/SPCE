// Library Includes
#include <cstdlib>

//Library Includes
#include "Enemy.h"
#include "Framework/AssetManager.h"

// Constants
#define POS_Y_MIN 100
#define POS_Y_MAX 900


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

void Enemy::Spawn()
{
	// Choose a random y position
	sf::Vector2f position;
	position.y = rand() % (POS_Y_MAX - POS_Y_MIN) + POS_Y_MIN;
	position.x = 1800.0f;

	SetPosition(position);
}

void Enemy::Kill()
{
	//Despawn the enemy add points
}