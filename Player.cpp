//Library Includes
#include "Player.h"
#include "Framework/AssetManager.h"
#include "Wall.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "SpeedUp.h"

//Constants
#define SPEED 500.0f
#define SPEEDANGLE 3.0f

Player::Player()
	: MovingObject()
	, m_animationSystem()
	, m_level(nullptr)
	, m_currenttime()
	, m_timecap(1.0f)

{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Jet.png"));

	// Set up the animation
	m_animationSystem.SetSprite(m_sprite);

	Animation& runDown = m_animationSystem.CreateAnimation("flying");
	runDown.AddFrame(AssetManager::GetTexture("graphics/Jet.png"));
	runDown.AddFrame(AssetManager::GetTexture("graphics/Jet2.png"));
	runDown.SetPlayBackSpeed(5);
	runDown.SetLoop(true);

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
		m_velocity.y = -SPEED;
		if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_velocity.y = -SPEED + (SPEED / SPEEDANGLE);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_velocity.y = SPEED;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_velocity.y = SPEED - (SPEED / SPEEDANGLE);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_velocity.x = -SPEED;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_velocity.x = -SPEED + (SPEED / SPEEDANGLE);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_velocity.x = SPEED;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_velocity.x = SPEED - (SPEED / SPEEDANGLE);
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


	// PLAYER SLOWMO CODE //
	// Check that the player is ready to use the ability
	// Once used make everything slow for 5 seconds






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

