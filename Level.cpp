// Framework includes
#include "Framework/AssetManager.h"

// Gamecode includes
#include "Level.h"

#include "Background.h"
#include "Midground.h"
#include "Wall.h"
#include "AbilityHolder.h"
#include "SlowMoSignal.h"
#include "Player.h"
#include "Enemy.h"
#include "Score.h"
#include "Controls.h"
#include "SpeedUp.h"
#include "Bullet.h"

// Library Includes
#include <iostream>
#include <fstream>

//Define
#define CAMERA_OFFSET 100.0f

Level::Level()
	: m_currentLevel(0)
	, m_player(nullptr)
	, m_updateList()
	, m_worldDrawList()
	, m_uiDrawList()
	, m_collisionList()
	, m_enemyList()
	, m_score(0)
	, m_enemytime()
	, m_enemytimecap(2.0f)
	, m_abilitytime()
	, m_abilitytimecap(30.0f)
	, m_Music()
{
	//open music file
	m_Music.openFromFile("audio/11 - Sync.ogg");
	// set music to loop when it finishes
	m_Music.setLoop(true);

	// load level
	LoadLevel(1);
}


void Level::Draw(sf::RenderTarget& _target)
{

	//Move the camera to the right slightly to keep left most wall off screen using offset

	sf::View camera = _target.getDefaultView();
	camera.setCenter(
		camera.getCenter().x + CAMERA_OFFSET,
		camera.getCenter().y
	);

	// Draw World Objects (sprites) //

	for (int i = 0; i < m_worldDrawList.size(); ++i)
	{
		if (m_worldDrawList[i]->isActive())
		{
			m_worldDrawList[i]->Draw(_target);
		}
	}
	///////////////////////////

	// Set Drawn objects to Camera //
	_target.setView(camera);
	///////////////////////////

	// Draw UI objects (text etc.) //
	for (int i = 0; i < m_uiDrawList.size(); ++i)
	{
		if (m_uiDrawList[i]->isActive())
		{
			m_uiDrawList[i]->Draw(_target);
		}
	}
	///////////////////
}

void Level::Update(sf::Time _frameTime)
{
	// Update list //
	// This list goes through all abjects game to upsate them each frame

	for (int i = 0; i < m_updateList.size(); ++i)
	{
		if (m_updateList[i]->isActive())
		{
			m_updateList[i]->Update(_frameTime);
		}
	}
	////////////////////

	// Collision List //
	// This loop checks each object in the game for collisions and calls their collision functions

	for (int i = 0; i < m_collisionList.size(); ++i)
	{
		GameObject* handler = m_collisionList[i].first;
		GameObject* collider = m_collisionList[i].second;

		if (handler->isActive() && collider->isActive())
		{
			if (handler->GetBounds().intersects(collider->GetBounds()))
			{
				
				collider->Collide(*handler);
				handler->Collide(*collider);
			}
		}
	}
	////////////////////


	// TIMER FOR ENEMY SPAWNING //
	// Timer adds up until it is above the time cap, once over the time cap another enemy is created and timer resets to constantly loop this code
	m_enemytime += _frameTime;

	if (m_enemytime.asSeconds() >= m_enemytimecap)
	{
		//Create new enemy
		Enemy* enemy = new Enemy();
		enemy->SetLevel(this);

		// Call enemy spawn function
		enemy->Spawn();
		// Add enemy to level
		AddObjects(enemy);
        m_enemyList.push_back(enemy);


		m_enemytime = sf::seconds(0.0f);
	}
	////////////////////////////////

	// TIMER FOR ABILITY SPAWNING //
	// Same functionality as the enemy spawn loop but for ability spawning

	m_abilitytime += _frameTime;

	if (m_abilitytime.asSeconds() >= m_abilitytimecap)
	{
		//Spawn new speedup ability
		SpeedUp* speedup = new SpeedUp();
		speedup->Spawn();
		// Add ability to level
		AddObjects(speedup);
		AddPlayerCollision(speedup);

		m_abilitytime = sf::seconds(0.0f);
	}
	///////////////////////////////

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

	// SET BACKGROUND //
	// Create the background
	for (int i = 0; i < 3; ++i)
	{
		Background* background = new Background();
		// Call background spawn function
		background->Spawn();
		// Add background to level
		AddObjects(background);
	}

	// Create the midground
	for (int i = 0; i < 3; ++i)
	{
		Midground* midground = new Midground();
		// Call background spawn function
		midground->Spawn();
		// Add background to level
		AddObjects(midground);
	}
	/////////////////////////////////////////////

	// PLAY MUSIC //
	m_Music.play();


	// Read in Level file //

	// Reading each character 1 by 1 from the fileff
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
		else if (ch == 'O')
		{
			AbilityHolder* abilityholder = new AbilityHolder();
			abilityholder->SetPosition(x, y);
			abilityholder->SetPlayer(m_player);
			m_updateList.push_back(abilityholder);
			m_worldDrawList.push_back(abilityholder);
			m_collisionList.push_back(std::make_pair(abilityholder, player));
		}
		else if (ch == 'S')
		{
			SlowMoSignal* slowmosignal = new SlowMoSignal();
			slowmosignal->SetPosition(x, y);
			slowmosignal->SetPlayer(m_player);
			m_updateList.push_back(slowmosignal);
			m_worldDrawList.push_back(slowmosignal);
			m_collisionList.push_back(std::make_pair(slowmosignal, player));
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
	/////////////////////////////////

	// Create ui objects //
	Score* score = new Score();
	score->SetLevel(this);
	m_score = 0;
	m_updateList.push_back(score);
	m_uiDrawList.push_back(score);

	Controls* controls = new Controls();
	m_updateList.push_back(controls);
	m_uiDrawList.push_back(controls);
	//////////////////////
}

//Whenever A new object is made during play, Add it to the list of game objects
void Level::AddObjects(GameObject* _toAdd)
{
	m_updateList.push_back(_toAdd);
	m_worldDrawList.push_back(_toAdd);	

	// Whenever a new object is added. We should check if it is currently slowmo
	_toAdd->SlowMo(m_player->GetSlowMo());
}

// Allows objects to collide with the enemy
void Level::AddEnemyCollision(GameObject* _collider)
{
	for (int i = 0; i < m_enemyList.size(); ++i)
	{
		if (m_enemyList[i]->isActive())
		{
			m_collisionList.push_back(std::make_pair(m_enemyList[i], _collider));
		}
	}
}

// Allows objects to collide with the player
void Level::AddPlayerCollision(GameObject* _collider)
{
	if (m_player->isActive())
	{
		m_collisionList.push_back(std::make_pair(m_player, _collider));
	}
}

// Changes the slow mo status of all objects in the game
void Level::SlowMo(bool _activeSlowMo)
{

	if (_activeSlowMo == true)
	{
		for (int i = 0; i < m_updateList.size(); ++i)
		{
			if (m_updateList[i]->isActive())
			{
				m_updateList[i]->SlowMo(true);
			}
		}
	}
	if (_activeSlowMo == false)
	{
		for (int i = 0; i < m_updateList.size(); ++i)
		{
			if (m_updateList[i]->isActive())
			{
				m_updateList[i]->SlowMo(false);
			}
		}
	}
}

// reloads level on death
void Level::ReloadLevel()
{
	LoadLevel(m_currentLevel);
}

// Lets score text file obtain the score value
int Level::GetScore()
{
	return m_score;
}

// Changes the score value
void Level::ChangeScore(int _change)
{
	m_score += _change;
}
