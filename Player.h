#pragma once

//Project Include
#include "Framework/MovingObject.h"
#include "Framework/AnimationSystem.h"
#include "Level.h"

class Player : public MovingObject
{
public:
	Player();

	//Overriding Methods
	void Update(sf::Time _frameTime);
	virtual void Collide(GameObject& _collider);

	// Public Player methods
	bool GetAbility();
	void HasAbility(bool _keychange);
	void Kill();
	void SetLevel(Level* _newLevel);

private:

	bool m_abilitycollected;
	AnimationSystem m_animationSystem;
	Level* m_level;

	sf::Time m_currenttime;
	float m_timecap;

	sf::Time m_slowtime;
	float m_slowtimecap;

	sf::Time m_slowtimeavailable;
	float m_slowtimeavailablecap;


};