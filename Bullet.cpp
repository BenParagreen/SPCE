
//Project Includes
#include "Bullet.h"
#include "Enemy.h"
#include "Framework/AssetManager.h"

#define SPEED 900.0f

Bullet::Bullet()
	: MovingObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Bullet.png"));
	// Constantly be moving right. X value determines speed
	m_velocity.x = SPEED;
	m_velocity.y = 0.0f;
}

void Bullet::Update(sf::Time _frameTime)
{
	//Call the update function manually on the parent class
	// this will actually move the character
	MovingObject::Update(_frameTime);

}

void Bullet::Fire(sf::Vector2f _target)
{
	SetPosition(_target);
}



void Bullet::Collide(GameObject& _collider)
{

    // Check if we are colliding with the enemy
	Enemy* enemyCollider = dynamic_cast<Enemy*>(&_collider);
	// check that the collision happened
	if (enemyCollider != nullptr)
	{
		m_active = false;
	}

}
