
//Project Includes
#include "EnemyBullet.h"
#include "Framework/AssetManager.h"

#define SPEED -900.0f

EnemyBullet::EnemyBullet()
	: MovingObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Bullet.png"));
	// Constantly be moving left. X value determines speed
	m_velocity.x = SPEED;
	m_velocity.y = 0.0f;
}

void EnemyBullet::Update(sf::Time _frameTime)
{
	// Call the update function manually on the parent class
	// this will actually move the bullet
	MovingObject::Update(_frameTime);

}

void EnemyBullet::Fire(sf::Vector2f _target)
{
	SetPosition(_target);
}



void EnemyBullet::Collide(GameObject& _collider)
{

}
