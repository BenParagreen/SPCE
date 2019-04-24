#include "Level.h"
#include "Wall.h"
#include "AbilityHolder.h"
#include "Player.h"
#include "Enemy.h"
#include "Score.h"
#include "SpeedUp.h"
#include "Bullet.h"

// Library Includes
#include <iostream>
#include <fstream>

Level::Level()
	: m_currentLevel(0)
	, m_player(nullptr)
	, m_updateList()
	, m_worldDrawList()
	, m_uiDrawList()
	, m_collisionList()
	, m_enemyList()
	, m_currenttime()
	, m_enemytimecap(3.0f)
	, m_currenttime2()
	, m_abilitytimecap(60.0f)
{
	LoadLevel(1);
}

void Level::Draw(sf::RenderTarget& _target)
{

	sf::View camera = _target.getDefaultView();


	for (int i = 0; i < m_worldDrawList.size(); ++i)
	{
		if (m_worldDrawList[i]->isActive())
		{
			m_worldDrawList[i]->Draw(_target);
		}

	}

	// Draw UI to the window
	_target.setView(_target.getDefaultView());
	// Draw UI objects

	for (int i = 0; i < m_uiDrawList.size(); ++i)
	{
		if (m_uiDrawList[i]->isActive())
		{
			m_uiDrawList[i]->Draw(_target);
		}

	}
}

void Level::Update(sf::Time _frameTime)
{
	for (int i = 0; i < m_updateList.size(); ++i)
	{
		if (m_updateList[i]->isActive())
		{
			m_updateList[i]->Update(_frameTime);
		}
	}


	for (int i = 0; i < m_collisionList.size(); ++i)
	{
		GameObject* handler = m_collisionList[i].first;
		GameObject* collider = m_collisionList[i].second;

		if (handler->isActive() && collider->isActive())
		{
			if (handler->GetBounds().intersects(collider->GetBounds()))
			{
				handler->Collide(*collider);
			}
		}
	}

	// Add Enemies to an Enemylist in order to handle collisions when a bullet connects

	for (int i = 0; i < m_enemyList.size(); ++i)
	{
		if (m_enemyList[i]->isActive())
		{
			m_enemyList[i]->Update(_frameTime);
		}
	}

	// TIMER FOR ENEMY SPAWNING //
	m_currenttime += _frameTime;

	if (m_currenttime.asSeconds() >= m_enemytimecap)
	{
		//Spawn new enemy
		Enemy* enemy = new Enemy();
		

		// Fire bullet passing in position
		enemy->Spawn();
		// Add enemy to level
		AddObjects(enemy);
        m_enemyList.push_back(enemy);


		m_currenttime = sf::seconds(0.0f);
	}

	// TIMER FOR ABILITY SPAWNING //

	m_currenttime2 += _frameTime;

	if (m_currenttime2.asSeconds() >= m_abilitytimecap)
	{
		//Spawn new enemy
		SpeedUp* speedup = new SpeedUp();
		// Fire bullet passing in position
		speedup->Spawn();
		// Add enemy to level
		AddObjects(speedup);

		m_currenttime2 = sf::seconds(0.0f);
	}

}

void Level::LoadLevel(int _levelToLoad)
{

	//Clean up old level

    //Delete any Data already in the level
	for (int i = 0; i < m_updateList.size(); ++i)
	{
		delete m_updateList[i];
	}

	for (int i = 0; i < m_enemyList.size(); ++i)
	{
		delete m_enemyList[i];
	}

	//Clear out lists
	m_updateList.clear();
	m_worldDrawList.clear();
	m_uiDrawList.clear();
	m_collisionList.clear();
	m_enemyList.clear();

	// Set the Current Level
	m_currentLevel = _levelToLoad;
	bool m_levelTrue = true;

	//Open File for Reading
	std::ifstream inFile;
	std::string fileName = "levels/Level" + std::to_string(m_currentLevel) + ".txt";
	inFile.open(fileName);

	//Make sure the file was opened
	if (!inFile)
	{
		std::cerr << "Unable to open file" + fileName;
		exit(1); //Call system to stop program with error
	}

	// Set the starting x and y oordinates used to position level objects
	float x = 0.0f;
	float y = 0.0f;

	//Define the spacing we will use for the grid
	const float X_SPACE = 100.0f;
	const float Y_SPACE = 100.0f;

	// create the player since other objects need to reference it
	Player* player = new Player();
	m_player = player;

	// Reading each character 1 by 1 from the file
	char ch;
    //Each time try to read next character in the text document
	// If successful, execute body of loop
	// noskipws means the file input will include white spaces 
	while (inFile >> std::noskipws >> ch)
	{
		// Perform actions based on what character was read in

		if (ch == ' ')
		{
			x += X_SPACE;
		}
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0;
		}
	    else if (ch == 'P')
		{
			player->SetPosition(x, y);
			player->SetLevel(this);
			m_updateList.push_back(player);
			m_worldDrawList.push_back(player);
		}
		else if (ch == 'W')
		{
			Wall* wall = new Wall();
			wall->SetPosition(x, y);
			m_updateList.push_back(wall);
			m_worldDrawList.push_back(wall);
			m_collisionList.push_back(std::make_pair(player, wall));
		}
		else if (ch == 'S')
		{
			SpeedUp* speedup = new SpeedUp();
			speedup->Spawn();
			m_updateList.push_back(speedup);
			m_worldDrawList.push_back(speedup);
			m_collisionList.push_back(std::make_pair(speedup, player));
		}
		else if (ch == 'O')
		{
			AbilityHolder* abilityholder = new AbilityHolder();
			abilityholder->SetPosition(x, y);
			m_updateList.push_back(abilityholder);
			m_worldDrawList.push_back(abilityholder);
			m_collisionList.push_back(std::make_pair(abilityholder, player));
		}
		else if (ch == '-')
		{

		}
		else
		{
			std::cerr << "Unrecognised character in level file:" << ch;
		}
		
	}

	inFile.close();

	// Create objects
	
	Score* score = new Score();
	score->SetPlayer(player);
	m_updateList.push_back(score);
	m_uiDrawList.push_back(score);

	// ADD ENEMY and ABILITY SPAWN LOOP
	// While level is active
	//while (m_levelTrue = true)
	//{
		// Spawn enemy every _ seconds,
		// if timesinceenemyspawned > enemytimer Spawn another enemy
		// After spawned, reduce spawn timer


		// Spawn Ability every _ seconds
	//}

}

//Whenever A new object is made during play, Add it to the list of game objects
void Level::AddObjects(GameObject* _toAdd)
{
	m_updateList.push_back(_toAdd);
	m_uiDrawList.push_back(_toAdd);			
}

void Level::AddCollision(GameObject* _collider)
{
	for (int i = 0; i < m_enemyList.size(); ++i)
	{
		if (m_enemyList[i]->isActive())
		{
			m_collisionList.push_back(std::make_pair(m_enemyList[i], _collider));
		}
	}
}


void Level::ReloadLevel()
{

	LoadLevel(m_currentLevel);
}


// Add list of enemies to level 
// Populate list, Create enemy then add to list
// Add function to level for adding collision with the enemies
// When bullet is spawned in player call that function