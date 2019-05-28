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
	, m_firetime()
	, m_firetimecap(1.0f)
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
	, m_speed(REGULARSPEED)
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

	// PLAYER MOVEMENT CODE //
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
	////////////////////////

	// PLAYER BULLET CODE //
	// When the player presses the F key it will set the bullets position and call it to spawn
	// Create a timer to restrict the amount of bullets that can be fired
	
	m_firetime += _frameTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		if (m_firetime.asSeconds() >= m_firetimecap)
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

			m_firetime = sf::seconds(0.0f);
		}
	}
	/////////////////////////////////////////////////////

	// PLAYER SLOWMO CODE //
	// Check that the player is ready to use the ability
	// Once used make everything slow for 4 seconds

	m_slowtimeavailable += _frameTime;

	// Check if it is available to let the slow mo signal change sprite
	if (m_slowtimeavailable.asSeconds() >= m_slowtimeavailablecap)
	{
		m_slowmoready = true;
	}

	// If it is available and the E button is pressed, do the ability
	if (m_slowtimeavailable.asSeconds() >= m_slowtimeavailablecap && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
        // start countdown till the ability runs out
		m_slowmocountdown = true;
		// Let level know to make objects slow mo
		m_level->SlowMo(true);
		// Tells the current slow mo status for new objects created to figure out if they should be slow mo
		m_slowmostatus = true;
		// The ability is no longer ready to use, lets slow mo signal change back to not being available
		m_slowmoready = false;

		// Reset availability timer
		m_slowtimeavailable = sf::seconds(0.0f);
	}
	
	// Code for countdown until slow mo is over
	if (m_slowmocountdown == true)
	{
       m_slowtime += _frameTime;
	   m_sprite.setTexture(AssetManager::GetTexture("graphics/Hand.png"));
	}
	
	// When the countdown is over reset everything to no longer be slow mo
	if(m_slowtime.asSeconds() > m_slowtimecap)
	{
		m_level->SlowMo(false);
		m_slowmostatus = false;
		m_slowmocountdown = false;
		m_slowtime = sf::seconds(0.0f);;
	}
	//////////////////////////////////////////////////////////////////

	// PLAYER SPEED UP CODE //
	// The player will pick up an speedup abilty and once it has been used it will increase the players speed for a few seconds

	// If the ability is collected and button is pressed, use it
	if (m_abilitycollected == true && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		// Begin countdown
		m_speedcountdown = true;	
		// Remove the stored ability to prevent it from getting used again
		m_abilitycollected = false;
	}

	// If the abilty is used, change the speed for the set amount of time
	if (m_speedcountdown == true)
	{
		m_speedtime += _frameTime;

		if (m_speedtime.asSeconds() <= m_speedtimecap)
		{
			m_speed = SPEEDABILITY;
		}
	}

	// Once the abilty has ran out of time reset to origional values
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

	// Check if it is an enemy bullet we are currently colliding with
	EnemyBullet* bulletCollider = dynamic_cast<EnemyBullet*>(&_collider);

	// If we collide with an enemy bullet we die
	if (bulletCollider != nullptr)
	{
		Kill();
	}
}

// Tells others if the ability is collected
bool Player::GetAbility()
{
	return m_abilitycollected;
}

// Lets the ability tell the player that its been collected
void Player::HasAbility(bool _abilitychange)
{
	m_abilitycollected = _abilitychange;
}

// reloads level on death
void Player::Kill()
{
	//Reload current Level
	if (m_level != nullptr)
		m_level->ReloadLevel();
}

// Tells player the level to add to
void Player::SetLevel(Level* _newLevel)
{
	m_level = _newLevel;
}

// Lets others check whether to be slow mo when they are spawned
bool Player::GetSlowMo()
{
	return m_slowmostatus;
}

// Tells the slow mo signal if the ability is ready
bool Player::GetSlowMoReady()
{
	return m_slowmoready;
}
