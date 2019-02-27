#include "Level.h"
#include "Wall.h"
#include "Exit.h"
#include "Player.h"
#include "Enemy.h"
#include "Score.h"
#include "Coin.h"
#include "Key.h"
#include "Hazard.h"

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
}

void Level::LoadLevel(int _levelToLoad)
{

	//Clean up old level

    //Delete any Data already in the level
	for (int i = 0; i < m_updateList.size(); ++i)
	{
		delete m_updateList[i];
	}

	//Clear out lists
	m_updateList.clear();
	m_worldDrawList.clear();
	m_uiDrawList.clear();
	m_collisionList.clear();

	// Set the Current Level
	m_currentLevel = _levelToLoad;

	//Set up New Level

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
			Enemy* enemy = new Enemy();
			enemy->SetPosition(x, y);
			m_updateList.push_back(enemy);
			m_worldDrawList.push_back(enemy);
			m_collisionList.push_back(std::make_pair(player, enemy));
		}
		else if (ch == 'C')
		{
			Coin* coin = new Coin();
			coin->SetPosition(x, y);
			m_updateList.push_back(coin);
			m_worldDrawList.push_back(coin);
			m_collisionList.push_back(std::make_pair(coin, player));
		}
		else if (ch == 'K')
		{
			Key* key = new Key();
			key->SetPosition(x, y);
			m_updateList.push_back(key);
			m_worldDrawList.push_back(key);
			m_collisionList.push_back(std::make_pair(key, player));
		}
		else if (ch == 'E')
		{

			Exit* exit = new Exit();
			exit->SetPosition(x,y);
			exit->SetPlayer(player);
			m_updateList.push_back(exit);
			m_worldDrawList.push_back(exit);
			m_collisionList.push_back(std::make_pair(exit, player));
		}
		else if (ch == 'H')
		{
			Hazard* hazard = new Hazard();
			hazard->SetPosition(x, y);
			m_updateList.push_back(hazard);
			m_worldDrawList.push_back(hazard);
			m_collisionList.push_back(std::make_pair(hazard, player));
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

}

void Level::ReloadLevel()
{
	LoadLevel(m_currentLevel);
}

void Level::LoadNextLevel()
{
	LoadLevel(m_currentLevel + 1);
}
