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
	int GetScore();
	void ChangeScore(int _change);
	bool GetKey();
	void HasKey(bool _keychange);
	void Kill();
	void SetLevel(Level* _newLevel);
	void AdvanceLevel();

private:

	int m_score;
	bool m_keycollected;
	AnimationSystem m_animationSystem;
	Level* m_level;
};