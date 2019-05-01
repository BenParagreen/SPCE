#pragma once

//Project Include
#include "Framework/MovingObject.h"


// Forward decleration since enemy calls level and level calls enemy 
class Level;


class Enemy : public MovingObject
{
public:
	Enemy();

	void Update(sf::Time _frameTime);
	void Spawn();

	//Override
	virtual void Collide(GameObject& _collider);
	
	void SetLevel(Level* _newLevel);

private:


	Level* m_level;

	sf::Time m_currenttime;
	float m_movetimecap;

	sf::Time m_currenttime2;
	float m_shoottimecap;

	int m_scoreValue;
};

