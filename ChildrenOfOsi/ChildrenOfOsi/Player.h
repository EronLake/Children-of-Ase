#pragma once
#include "stdafx.h"
#include "Hero.h"
class Player :
	public Hero
{
public:
	Player();
	Player(float x, float y, bool col);
	~Player();
	void setTalkDist(float dist);
	Rectangle talk;
};

