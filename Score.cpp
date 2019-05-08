//Project Includes 
#include "Score.h"
#include "Framework/AssetManager.h"

Score::Score()
	: TextObject() // Initialise parent class
	, m_level (nullptr)
{
	m_Text.setFont(AssetManager::GetFont("fonts/mainFont.ttf"));
	m_Text.setString("Score:0");


	sf::Vector2f position;
	position.y = 10;
	position.x = 110;
	SetPosition(position);

}

void Score::Update(sf::Time _frametime)
{
	if (m_level != nullptr)
	{
		int score = m_level->GetScore();
		m_Text.setString("Score: "+ std::to_string(score));
	}	
}

void Score::SetLevel(Level* _playthrough)
{
	m_level = _playthrough;
}