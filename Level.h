#pragma once

//Project Includes
#include "Framework/GameObject.h"
#include "Enemy.h"
#include <vector>

class Level
{

public:

	Level();

	void Draw(sf::RenderTarget& _target);
    void Update(sf::Time _frametime);
	void LoadLevel(int _levelToLoad);
	void AddObjects(GameObject* _toAdd);
	void AddCollision(GameObject* _collider );
	void ReloadLevel();


private:

	int m_currentLevel;
	GameObject* m_player;
	std::vector<GameObject*> m_updateList;
	std::vector<GameObject*> m_worldDrawList;
	std::vector<GameObject*> m_uiDrawList;

    std::vector<Enemy*> m_enemyList;
	

	sf::Time m_currenttime;
	float m_enemytimecap;

	sf::Time m_currenttime2;
	float m_abilitytimecap;

	std::vector<std::pair<GameObject*, GameObject*>> m_collisionList;
};