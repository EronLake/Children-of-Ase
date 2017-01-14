#pragma once
#include "LivingObj.h"
class Player :
	public LivingObj
{
public:
	Player();
	Player(float x, float y, bool col);
	~Player();
};

