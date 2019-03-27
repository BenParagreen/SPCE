
//Project Includes
#include "Bullet.h"
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
