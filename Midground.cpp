//Project Includes
#include "Midground.h"
#include "Framework/AssetManager.h"

#define SPEED -300.0f


float Midground::s_furthestPoint = 0;

Midground::Midground()
	: MovingObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/SpaceMidground.png"));
	// Constantly be moving left. X value determines speed
	m_velocity.x = SPEED;
	m_velocity.y = 0.0f;
	m_falloffpoint.x = -m_sprite.getGlobalBounds().width * 2;
	m_spawnposition.y = 0;

}

void Midground::Spawn()
{
	m_spawnposition.x = s_furthestPoint;
	m_sprite.setPosition(m_spawnposition);
	s_furthestPoint += m_sprite.getGlobalBounds().width;
}

void Midground::Update(sf::Time _frameTime)
{
	// Call the update function manually on the parent class
	// this will actually move the background
	MovingObject::Update(_frameTime);

	// Get the current position
	currentPosition = m_sprite.getPosition();

	// detect if off screen left, if so, call spawn to position to the right
	if (currentPosition.x <= m_falloffpoint.x)
	{
		s_furthestPoint = m_sprite.getGlobalBounds().width;
		m_spawnposition.x = s_furthestPoint;
		m_sprite.setPosition(m_spawnposition);
	}


	// Code if the object has been slowed down
	if (m_slowed == true)
	{
		// Set new velocity
		m_velocity.x = SPEED * 5;
		m_sprite.setTexture(AssetManager::GetTexture("graphics/MidgroundWarped.png"));

	}

	if (m_slowed == false)
	{
		// Revert back to original speed
		m_velocity.x = SPEED;

		m_sprite.setTexture(AssetManager::GetTexture("graphics/SpaceMidground.png"));
	}
}
