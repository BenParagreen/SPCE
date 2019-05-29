//Project Includes 
#include "Hypeman.h"
#include "Framework/AssetManager.h"

Hypeman::Hypeman()
	: TextObject() // Initialise parent class
	, m_level(nullptr)
{
	m_Text.setFont(AssetManager::GetFont("fonts/mainFont.ttf"));

	sf::Vector2f position;
	position.y = 10;
	position.x = 1600;
	SetPosition(position);

}

void Hypeman::Update(sf::Time _frametime)
{
	if (m_level != nullptr)
	{
		int score = m_level->GetScore();
		if (score >= 10)
			m_Text.setString("Killer");
		if (score >= 100)
			m_Text.setString("Killentury");
		if (score >= 300)
			m_Text.setString("Killman");
		if (score >= 500)
			m_Text.setString("Killemall");
		if (score >= 1000)
			m_Text.setString("Killenium");
		if (score >= 2000)
			m_Text.setString("Killenium2 Electric Boogaloo");
		if (score >= 3000)
			m_Text.setString("Frigenkillen");
		if (score >= 4000)
			m_Text.setString("Killdrupelair");
		if (score >= 5000)
			m_Text.setString("Unfriggenkillable");
		if (score >= 6000)
			m_Text.setString("Killeminstant");
		if (score >= 7000)
			m_Text.setString("Killanarmada");
		if (score >= 8000)
			m_Text.setString("Killatimezone");
		if (score >= 9000)
			m_Text.setString("OverKillin");
		if (score >= 10000)
			m_Text.setString("Demon");
		if (score >= 20000)
			m_Text.setString("Death");
		if (score >= 30000)
			m_Text.setString("Time");

	}
}

void Hypeman::SetLevel(Level* _playthrough)
{
	m_level = _playthrough;
}