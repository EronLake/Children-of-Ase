#pragma once
#include "Hero.h"
class Player :
	public Hero
{
public:
	Player();
	Player(float x, float y, bool col);
	~Player();
};

