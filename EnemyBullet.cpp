
//Project Includes
#include "EnemyBullet.h"
#include "Framework/AssetManager.h"

#define SPEED -900.0f

EnemyBullet::EnemyBullet()
	: MovingObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Bullet.png"));
	m_velocity.y = 0.0f;
	m_velocity.x = SPEED;
}

void EnemyBullet::Update(sf::Time _frameTime)
{
	// Call the update function manually on the parent class
	// this will actually move the bullet
	MovingObject::Update(_frameTime);

    // Code if the object has been slowed down
	if (m_slowed == true)
	{
		// Set new velocity
		m_velocity.x = SPEED / 5;
	}

	if (m_slowed == false)
	{
		// Revert back to original speed
		m_velocity.x = SPEED; 
	}
}


void EnemyBullet::Fire(sf::Vector2f _target)
{
	SetPosition(_target);
}


void EnemyBullet::Collide(GameObject& _collider)
{
	// Do nothing (Level will handle a full reset)
}
