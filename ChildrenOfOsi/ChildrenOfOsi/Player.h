#pragma once
#include "stdafx.h"
#include "Hero.h"
class Player :
	public Hero
{
public:
	Player();
	Player(float x, float y, bool col);
	Player(Vector2f p_topLeft, float p_width, float p_height);
	~Player();
	void setTalkDist(float dist);
private:
	Rectangle talk;
};

