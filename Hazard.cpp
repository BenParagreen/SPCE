
//Project Includes
#include "Hazard.h"
#include "Framework/AssetManager.h"
#include "Player.h"

Hazard::Hazard()
	: SpriteObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Obstacle.png"));
}

void Hazard::Collide(GameObject& _collider)
{

	// Only do something if colliding with player

	Player* castPlayer = dynamic_cast<Player*>(&_collider);

	if (castPlayer != nullptr)
	{
		// Touched by the player
		// Kill player
		castPlayer->Kill();
	}

}