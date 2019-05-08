
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
}

void Background::Spawn()
{
	// Choose a random y position
	sf::Vector2f position;
	
	position.y = 0;
	position.x = s_furthestPoint;
	m_sprite.setPosition(position);

	// Update the furthest position to the right
	// (our platform is now furthest to the right)
	s_furthestPoint = position.x + m_sprite.getGlobalBounds().width;
	
}

void Background::Update(sf::Time _frameTime)
{
	// Call the update function manually on the parent class
	// this will actually move the background
	MovingObject::Update(_frameTime);



	// detect if off screen left, if so, use same code from spawn function to position to the right.
	// in fact just call spawn
	if (m_fallOffPoint <= 0)
	{
		Spawn();
	}
}
