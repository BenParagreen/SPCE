
//Project Includes 
#include "Wall.h"
#include "Framework/AssetManager.h"

Wall::Wall()
	: SpriteObject() // Initialise parent class
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/BrickWall2.png"));
	// TODO: TEMP REMOVE
}