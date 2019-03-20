
//Project Includes
#include "Bullet.h"
#include "Framework/AssetManager.h"
#include "Enemy.h"

Bullet::Bullet()
	: MovingObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Bullet.png"));
	m_velocity.x = 50.0f;
	m_velocity.y = 0.0f;
}

void Bullet::Update(sf::Time _frameTime)
{
	//Call the update function manually on the parent class
	// this will actually move the character
	MovingObject::Update(_frameTime);
}


//void Bullet::Collide(GameObject& _collider)
//{

	// Only do something if colliding with Enemy

	//Enemy* castEnemy = dynamic_cast<Enemy*>(&_collider);

	//if (castEnemy != nullptr)
	//{
		// Touched by the player
		// Kill player
		//castEnemy->Kill();
	//}

//}