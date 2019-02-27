
//Project includes 
#include "SpriteObject.h"

SpriteObject::SpriteObject()
	: GameObject() //Always initialise your parent class in your constructor
	, m_sprite()
{
	
}

void SpriteObject::Draw(sf::RenderTarget& _Target)
{
	_Target.draw(m_sprite);
}

sf::FloatRect SpriteObject::GetBounds() //function for setting up bounding boxes
{
	return m_sprite.getGlobalBounds();
}

void SpriteObject::SetPosition(sf::Vector2f _Position)
{
	m_sprite.setPosition(_Position);
}

void SpriteObject::SetPosition(float _X, float _Y)
{
	m_sprite.setPosition(_X, _Y);
}

sf::Vector2f SpriteObject::GetPosition()
{
	return m_sprite.getPosition();
}