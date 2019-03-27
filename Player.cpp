//Library Includes
#include "Player.h"
#include "Framework/AssetManager.h"
#include "Wall.h"
#include "Bullet.h"

//Constants
#define SPEED 500.0f
#define SPEEDANGLE 3.0f

Player::Player()
	: MovingObject()
	, m_score(0)
	, m_animationSystem()
	, m_level(nullptr)

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

	//Use the keyboard function to check which keys are currently held down
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

	//bulletPosition = new Vector2()

	// When the player presses the F key it will set the bullets position and call it to spawn
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		// Create a timer to restrict the amount of bullets fired

		// Store Player position for bullet position to go off of
		sf::Vector2f position;
		position = m_sprite.getPosition();
		position.x = position.x + 120.0f;
		position.y = position.y + 48.0f;
		//Create the bullet and fire
		Bullet* bullet = new Bullet();
		bullet->Fire(position);
		// Send to level for it to take care of bullet once it has appeared on screen
		m_level->AddObjects(bullet);
	}

	//Call the update function manually on the parent class
	// this will actually move the character
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
		//Returm to our previous position that we just moved from
		m_sprite.setPosition(m_previousPosition);

		// NOTE //
		// This is not the best method for creating wall collision
		// It results in "sticky" wall (does not allow you to slide against them
		// It is quicker and easier to implement though so it is being used in this game
	}
}


int Player::GetScore()
{
	return m_score;
}

void Player::ChangeScore(int _change)
{
	m_score += _change;
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

