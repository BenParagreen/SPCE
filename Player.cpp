//Library Includes
#include "Player.h"
#include "Framework/AssetManager.h"
#include "Wall.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "SpeedUp.h"

//Constants
#define SPEEDANGLE 3.0f
#define SPEEDABILITY 800.0f
#define REGULARSPEED 500.0f

Player::Player()
	: MovingObject()
	, m_animationSystem()
	, m_level(nullptr)
	, m_currenttime()
	, m_timecap(1.0f)
	, m_slowtime()
	, m_slowtimecap(4.0f)
	, m_slowtimeavailable()
	, m_slowtimeavailablecap(10.0f)
	, m_slowmostatus(false)
	, m_slowmoready(false)
	, m_slowmocountdown(false)
	, m_speedtime()
	, m_speedtimecap(3.0f)
	, m_speedcountdown(false)
	, m_speed(500.0f)
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Jet.png"));

	// Set up the animation
	m_animationSystem.SetSprite(m_sprite);

	Animation& fly = m_animationSystem.CreateAnimation("flying");
	fly.AddFrame(AssetManager::GetTexture("graphics/Jet.png"));
	fly.AddFrame(AssetManager::GetTexture("graphics/Jet2.png"));
	fly.SetPlayBackSpeed(5);
	fly.SetLoop(true);

	m_animationSystem.Play("flying");
}

void Player::Update(sf::Time _frameTime)
{
	//First assume no keys are pressed
	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;
	
	m_currenttime += _frameTime;

	//Use the keyboard function to check which keys are currently held down and solve direction to move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_velocity.y = -m_speed;
		m_sprite.setTexture(AssetManager::GetTexture("graphics/JetUp.png"));
		if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_velocity.y = -m_speed + (m_speed / SPEEDANGLE);
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_velocity.y = m_speed;
		m_sprite.setTexture(AssetManager::GetTexture("graphics/JetDown.png"));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_velocity.y = m_speed - (m_speed / SPEEDANGLE);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_velocity.x = -m_speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_velocity.x = -m_speed + (m_speed / SPEEDANGLE);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_velocity.x = m_speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_velocity.x = m_speed - (m_speed / SPEEDANGLE);
	}

	// PLAYER BULLET CODE //
	// When the player presses the F key it will set the bullets position and call it to spawn
	// Create a timer to restrict the amount of bullets fired
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		if (m_currenttime.asSeconds() >= m_timecap)
		{
			// Take player position and use to find bullet position
			sf::Vector2f position;
			position = m_sprite.getPosition();
			position.x = position.x + 120.0f;
			position.y = position.y + 48.0f;

			//Create the bullet and fire
			Bullet* bullet = new Bullet();
			// Fire bullet passing in position
			bullet->Fire(position);
			// Send to level for it to take care of bullet once it has appeared on screenff
			m_level->AddObjects(bullet);
			m_level->AddEnemyCollision(bullet);

			m_currenttime = sf::seconds(0.0f);
		}
	}
	/////////////////////////////////////////////////////

	// PLAYER SLOWMO CODE //
	// Check that the player is ready to use the ability
	// Once used make everything slow for 5 seconds

	m_slowtimeavailable += _frameTime;

	if (m_slowtimeavailable.asSeconds() >= m_slowtimeavailablecap)
	{
		m_slowmoready = true;
	}


	if (m_slowtimeavailable.asSeconds() >= m_slowtimeavailablecap && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
        
		m_slowmocountdown = true;

		m_level->SlowMo(true);
		m_slowmostatus = true;
		m_slowmoready = false;

		
			
		m_slowtimeavailable = sf::seconds(0.0f);

	}
	
	if (m_slowmocountdown == true)
	{
       m_slowtime += _frameTime;
	   m_sprite.setTexture(AssetManager::GetTexture("graphics/Hand.png"));
	}
	

	if(m_slowtime.asSeconds() > m_slowtimecap)
	{
		m_level->SlowMo(false);
		m_slowmostatus = false;
		m_slowmocountdown = false;
		m_slowtime = sf::seconds(0.0f);;
	}
	//////////////////////////////////////////////////////////////////

	// Player Speed up code
	

	//After a few seconds stop and change value of time spent moving
	if (m_abilitycollected == true && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_speedcountdown = true;		
		m_abilitycollected = false;
	}

	if (m_speedcountdown == true)
	{
		m_speedtime += _frameTime;

		if (m_speedtime.asSeconds() <= m_speedtimecap)
		{
			m_speed = SPEEDABILITY;
		}
	}


	if (m_speedtime.asSeconds() > m_speedtimecap)
	{
		
		m_speed = REGULARSPEED;
		m_speedcountdown = false;
		m_speedtime = sf::seconds(0.0f);
	}

	//////////////////////////////////////////////////////////////////

	//Call the update function manually on the parent class
	// this will move the character
	MovingObject::Update(_frameTime);

	//Process Animations
	m_animationSystem.Update(_frameTime);
}

void Player::Collide(GameObject& _collider)
{
	//Only do something if what the player touched was the wall
	//Dynamic cast the GameObject reference into a wall pointer
	// if it succeeds it was a wall
	Wall* wallCollider = dynamic_cast<Wall*>(&_collider);

	//If it was a wall we hit we need to move ourselves outside the walls bounds
	// aka, our previous position
	if (wallCollider != nullptr)
	{
		//The player hit a wall
		//Return to our previous position that we just moved from
		m_sprite.setPosition(m_previousPosition);
	}

	// Check if it is an speedup we are currently colliding with
	SpeedUp* speedCollider = dynamic_cast<SpeedUp*>(&_collider);

	// If we collide with a speedup we store it
	if (speedCollider != nullptr)
	{
		HasAbility(true);
	}


	// Check if it is an enemy we are currently colliding with
	EnemyBullet* bulletCollider = dynamic_cast<EnemyBullet*>(&_collider);

	// If we collide with an enemy we die
	if (bulletCollider != nullptr)
	{
		Kill();
	}
}

bool Player::GetAbility()
{
	return m_abilitycollected;
}

void Player::HasAbility(bool _abilitychange)
{
	m_abilitycollected = _abilitychange;
}

void Player::Kill()
{
	//Reload current Level
	if (m_level != nullptr)
		m_level->ReloadLevel();
}

void Player::SetLevel(Level* _newLevel)
{
	m_level = _newLevel;
}


bool Player::GetSlowMo()
{
	return m_slowmostatus;
}

bool Player::GetSlowMoReady()
{
	return m_slowmoready;
}
