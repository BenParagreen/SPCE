#pragma once

//Project Includes
#include "Framework/GameObject.h"
#include "Enemy.h"
#include <vector>

class Player;

class Level
{

public:

	Level();

	void Draw(sf::RenderTarget& _target);
    void Update(sf::Time _frametime);
	void LoadLevel(int _levelToLoad);
	void AddObjects(GameObject* _toAdd);
	void AddEnemy(GameObject* _toAdd);
	void AddEnemyCollision(GameObject* _collider );
	void AddPlayerCollision(GameObject* _collider);
	void SlowMo(bool _activeSlowMo);
	void ReloadLevel();

	int GetScore();
	void ChangeScore(int _change);


private:

	int m_currentLevel;
	Player* m_player;


	std::vector<GameObject*> m_updateList;
	std::vector<GameObject*> m_worldDrawList;
	std::vector<GameObject*> m_uiDrawList;

	// List for enemy collisions
    std::vector<Enemy*> m_enemyList;

	//The score of the player
	int m_score;


	// Timers for the enemy spawn loop
	sf::Time m_currenttime;
	float m_enemytimecap;

	// Timer for the ability spawn loop
	sf::Time m_currenttime2;
	float m_abilitytimecap;

	std::vector<std::pair<GameObject*, GameObject*>> m_collisionList;

	sf::Music m_Music;

};