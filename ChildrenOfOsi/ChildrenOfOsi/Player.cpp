#include "stdafx.h"
#include "Player.h"



Player::Player()
{
}

Player::Player(float x, float y, bool col):Hero(x,y,col)
{
}

Player::Player(Vector2f p_topLeft, float p_width, float p_height):Hero(p_topLeft,p_width,p_height)
{
}


Player::~Player()
{
}

void Player::setTalkDist(float dist)
{
	talk.setX((*this).getX()-dist);
	talk.setY((*this).getY()-dist);
	talk.setWidth((*this).getWidth()+(2*dist));
	talk.setHeight((*this).getHeight()+(2*dist));
}
