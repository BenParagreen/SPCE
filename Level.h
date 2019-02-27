#pragma once

//Project Includes
#include "Framework/GameObject.h"

class Level
{

public:

	Level();

	void Draw(sf::RenderTarget& _target);
    void Update(sf::Time _frametime);
	void LoadLevel(int _levelToLoad);
	void ReloadLevel();
	void LoadNextLevel();

private:

	int m_currentLevel;
	GameObject* m_player;
	std::vector<GameObject*> m_updateList;
	std::vector<GameObject*> m_worldDrawList;
	std::vector<GameObject*> m_uiDrawList;

	std::vector<std::pair<GameObject*, GameObject*>> m_collisionList;
};