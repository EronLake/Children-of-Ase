#pragma once
#include "stdafx.h"
#include "Hero.h"
#include "Memory.h"
class Player :
	public Hero
{
public:
	Player();

	Player(int name, float x, float y, bool col);
	Player(int name, Vector2f p_topLeft, float p_width, float p_height);
	~Player();
	void setTalkDist(float dist);
	void updateTalk();
	Rectangle talk;
	float distance;
	Action* quest;
	Action* cur_action;

	//don't need these because they are inherated from hero
	//int mem_counter;
	//vector<Memory*> memories;
};

