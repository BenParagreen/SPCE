//Project Includes 
#include "Score.h"
#include "Framework/AssetManager.h"

Score::Score()
	: TextObject() // Initialise parent class
	, m_player (nullptr)
{
	m_Text.setFont(AssetManager::GetFont("fonts/mainFont.ttf"));
	m_Text.setString("Score:0");
}

void Score::Update(sf::Time _frametime)
{
	if (m_player != nullptr)
	{
		int score = m_player->GetScore();
		m_Text.setString("Score: "+ std::to_string(score));
	}	
}

void Score::SetPlayer(Player* _player)
{
	m_player = _player;
}