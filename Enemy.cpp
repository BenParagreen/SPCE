// Library Includes
#include <cstdlib>

//Library Includes
#include "Enemy.h"
#include "Player.h"
#include "Level.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "Framework/AssetManager.h"

// Constants
#define POS_Y_MIN 100
#define POS_Y_MAX 900

#define VELOCITY_X_MIN -200
#define VELOCITY_X_MAX -40

Enemy::Enemy()
	: MovingObject()
	, m_level(nullptr)
	, m_currenttime()
	, m_movetimecap(3.0f)
	, m_currenttime2()
	, m_shoottimecap(2.0f)
	, m_scoreValue(10)
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/EnemyShip.png"));
	m_velocity.x = rand() % (VELOCITY_X_MAX - VELOCITY_X_MIN) + VELOCITY_X_MIN;
	m_velocity.y = 0.0f;
}

void Enemy::Update(sf::Time _frameTime)
{
	//Call the update function manually on the parent class
	// this will actually move the character
	MovingObject::Update(_frameTime);
	
	m_currenttime += _frameTime;

	//After a few seconds stop and change value of time spent moving
	if (m_currenttime.asSeconds() >= m_movetimecap)
	{
		m_velocity.x = 0;
	}

	//Every couple of seconds fire a bullet

	m_currenttime2 += _frameTime;

	if (m_currenttime2.asSeconds() >= m_shoottimecap)
	{
		// Take ship position and use to find bullet position
		sf::Vector2f position;
		position = m_sprite.getPosition();
		position.x = position.x;
		position.y = position.y + 48;

		//Create the bullet and fire
	    EnemyBullet* enemybullet = new EnemyBullet();
		// Fire bullet passing in position
		enemybullet->Fire(position);
		
		// Send to level for it to take care of bullet once it has appeared on screenff
		m_level->AddObjects(enemybullet);
        m_level->AddPlayerCollision(enemybullet);
		//Reset Timer
		m_currenttime2 = sf::seconds(0.0f);
	}

	    // Code if the object has been slowed down
	if (m_slowed == true && m_velocity.x != 0)
	{
		m_velocity.x = - 40;
	}
	if (m_slowed == false && m_oldvelocity.x != 0)
	{
	    // Revert back to original speed
		m_velocity.x = m_oldvelocity.x;
	}

	if (m_slowed == true )
	{
		m_sprite.setTexture(AssetManager::GetTexture("graphics/Bannan.png"));
		m_shoottimecap = 3.0f;
	}
	if (m_slowed == false)
	{
		m_sprite.setTexture(AssetManager::GetTexture("graphics/EnemyShip.png"));
		m_shoottimecap = 2.0f;
	}
}

void Enemy::Spawn()
{
	// Choose a random y position
	sf::Vector2f position;
	position.y = rand() % (POS_Y_MAX - POS_Y_MIN) + POS_Y_MIN;
	position.x = 2000.0f;

	SetPosition(position);
}


void Enemy::Collide(GameObject& _collider)
{
	Bullet* bulletCollider = dynamic_cast<Bullet*>(&_collider);

	if (bulletCollider != nullptr)
	{
		m_level->ChangeScore(10);
		m_active = false;
	}

	//if colliding with anything else
	// do nothing
}

void Enemy::SetLevel(Level* _newLevel)
{
	m_level = _newLevel;
}
