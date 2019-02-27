#pragma once

//Project Includes
#include "Framework/SpriteObject.h"

class Hazard
	: public SpriteObject
{
public:
	Hazard();

	//Overriding Methods
    void Collide(GameObject& _collider);
};