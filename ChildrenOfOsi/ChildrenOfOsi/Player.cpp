#include "stdafx.h"
#include "Player.h"



Player::Player()
{
}

Player::Player(float x, float y, bool col):Hero(x,y,col)
{
}


Player::~Player()
{
}

{
	talk.setX((*this).getX()-dist);
	talk.setY((*this).getY()-dist);
	talk.setWidth((*this).getWidth()+(2*dist));
	talk.setHeight((*this).getHeight()+(2*dist));
