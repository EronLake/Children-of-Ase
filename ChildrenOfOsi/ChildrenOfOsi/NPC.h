#pragma once
#include "stdafx.h"
#include "LivingObj.h"
#include "Factions.h"

#define WANDER 0
#define WAIT 1
#define SEEK 2

class NPC :
	public LivingObj
{
public:
	NPC();
	NPC(float x, float y, bool col);
	NPC(Vector2f p_topLeft, float p_width, float p_height);
	~NPC();
	void setFaction(int f);
	int getFaction();
	void setSpeed(float);
	float getSpeed();
	void setDiagSpeed(float);
	float getDiagSpeed();
	void setDiagXSpeed(float);
	float getDiagXSpeed();
	void setDiagYSpeed(float);
	float getDiagYSpeed();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void setMode(int m);
	int getMode();

	Vector2f destination;
	Vector2f waypoint;
	vector<Vector2f> waypoints;

private:
	int faction;
	float speed;
	float diagSpeed;
	float diagXSpeed;
	float diagYSpeed;
	
	int move_mode;
};

