
//Project Includes
#include "Background.h"
#include "Framework/AssetManager.h"

#define SPEED -300.0f


float Background::s_furthestPoint = 0;

Background::Background()
	: MovingObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/background.jpg"));
	// Constantly be moving left. X value determines speed
	m_velocity.x = SPEED;
	m_velocity.y = 0.0f;
	m_falloffpoint.x = - m_sprite.getGlobalBounds().width * 2;
	m_spawnposition.y = 0;
}

void Background::Spawn()
{
	m_spawnposition.x = s_furthestPoint;
	s_furthestPoint += m_sprite.getGlobalBounds().width;
	m_sprite.setPosition(m_spawnposition);
}

void Background::Update(sf::Time _frameTime)
{
	// Call the update function manually on the parent class
	// this will actually move the background
	MovingObject::Update(_frameTime);

	// Get the current position
	sf::Vector2f currentPosition = m_sprite.getPosition();

	// detect if off screen left, if so, call spawn to position to the right
	if (currentPosition.x <= m_falloffpoint.x)
	{
		Spawn();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		// Code if the object has been slowed down
		if (m_slowed == true)
		{
     		// Set new velocity
			m_velocity.x = -SPEED * 2;

			m_sprite.setTexture(AssetManager::GetTexture("graphics/BackgroundWarped.png"));
		}

	}		
	if (m_slowed == false)
	{
		// Revert back to original speed
		m_velocity.x = SPEED;

		m_sprite.setTexture(AssetManager::GetTexture("graphics/background.jpg"));
	}
}
