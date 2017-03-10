#include "stdafx.h"
#include "NPC.h"
using namespace std;


NPC::NPC()
{
}

NPC::NPC(float x, float y, bool col) :LivingObj(x, y, col)
{
	move_mode = WAIT;
	speed = 6.0F;
	diagXSpeed = sqrt((speed*speed) / 2);
	diagYSpeed = sqrt((speed*speed) / 2);
	
}

NPC::NPC(Vector2f p_topLeft, float p_width, float p_height):LivingObj(p_topLeft,p_width,p_height)
{
	move_mode = WAIT;
	speed = 6.0F;
	diagXSpeed = sqrt((speed*speed) / 2);
	diagYSpeed = sqrt((speed*speed) / 2);
}

NPC::~NPC()
{
}

void NPC::setSpeed(float s)
{
	speed=s;
}

float NPC::getSpeed()
{
	return speed;
}

void NPC::setDiagSpeed(float s)
{
	diagSpeed = s;
}

float NPC::getDiagSpeed()
{
	return diagSpeed;
}
void NPC::setDiagXSpeed(float s)
{
	diagXSpeed = s;
}

float NPC::getDiagXSpeed()
{
	return diagXSpeed;
}
void NPC::setDiagYSpeed(float s)
{
	diagYSpeed = s;
}
float NPC::getDiagYSpeed()
{
	return diagYSpeed;
}

void NPC::moveRight()
{
	(*this).shiftX(speed);
}

void NPC::moveLeft()
{
	(*this).shiftX(-speed);
}

void NPC::moveUp()
{
	(*this).shiftY(speed);
}

void NPC::moveDown()
{
	(*this).shiftY(-speed);
}
void NPC::setMode(int m)
{
	move_mode = m;
}
int NPC::getMode()
{
	return move_mode;
}