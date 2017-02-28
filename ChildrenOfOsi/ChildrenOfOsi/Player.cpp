#include "stdafx.h"
#include "Player.h"



Player::Player()
{
}

Player::Player(int name, float x, float y, bool col):Hero(name,x,y,col)
{
	float speed = 6.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
}

Player::Player(int name, Vector2f p_topLeft, float p_width, float p_height):Hero(name,p_topLeft,p_width,p_height)
{
	float speed = 6.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
}


Player::~Player()
{
}

void Player::setTalkDist(float dist)
{
	distance = dist;
	talk.setX((*this).getX()-dist);
	talk.setY((*this).getY()-dist);
	talk.setWidth((*this).getWidth()+(2*dist));
	talk.setHeight((*this).getHeight()+(2*dist));
}

void Player::updateTalk()
{
	talk.setX((*this).getX() - distance);
	talk.setY((*this).getY() - distance);
	talk.setWidth((*this).getWidth() + (2 * distance));
	talk.setHeight((*this).getHeight() + (2 * distance));
}

void Player::addRelationship(int p_HeroNum, Relationship * p_relations)
{
	relationMap[p_HeroNum] = p_relations;
}

void Player::removeRelation(int p_heroNum)
{
	relationMap.erase(p_heroNum);
}

Relationship * Player::getRelation(int p_heroNum)
{
	return relationMap[p_heroNum];
}
