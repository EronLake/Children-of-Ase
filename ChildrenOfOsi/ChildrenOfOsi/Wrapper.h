#pragma once
#include "Player.h"
#include "Attack.h"

class Wrapper
{
public:
	Wrapper();
	Wrapper(Player* p);
	Wrapper(Hero* h);
	Wrapper(SplSoldier* sp);
	Wrapper(Soldier* s);
	Wrapper(NPC* n);
	Wrapper(LivingObj* l);
	Wrapper(WorldObj* w);
	~Wrapper();
	//WorldObj
	//--------
	void setLoc(Vector2f l);
	Vector2f getLoc();
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	void shiftX(float dist);
	void shiftY(float dist);
	void setRot(Vector2f r);
	Vector2f getRot();
	void setRotX(float x);
	void setRotY(float y);
	float getRotX();
	float getRotY();
	void shiftRotX(float dist);
	void shiftRotY(float dist);
	void setCollision(bool c);
	bool getCollision();
	void setInteractable(bool i);
	bool getInteractable();
	void setWidth(float w);
	float getWidth();
	void setHeight(float h);
	float getHeight();
	Sprite getSprite();
	void setSprite(Sprite s);
	Sprite* sprite;
	void animateObj();
	void setName(string n);
	string getName();
	void drawObj(float _x, float _y);
	Rectangle* getBody();//new
	void offsetBody(int i, float x1, float x2, float y1, float y2);
	void _print();
	//LivingObj
	//---------
	int getHealth();
	void setHealth(int h);
	bool getAlive();
	void setAlive(bool v);
	void addHealth(int h);
	//NPC
	//---
	void setFaction(int f);
	int getFaction();
	void setSpeed(float);
	float getSpeed();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	//Soldier
	//-------
	int getAtk();
	void setAtk(int a);
	void goAtk(LivingObj *target);
	void setInCombat(bool c);
	bool getInCombat();
	//SPLSoldier
	//-------
	int getAse();
	void setAse(int a);
	//Hero
	//----
	void setTalkDist(float dist);
	//Player
	//------
	Rectangle* talk;
private:
	int type;
	Player* player;//6
	Hero* hero;//5
	SplSoldier* special;//4
	Soldier* soldier;//3
	NPC* npc;//2
	LivingObj* living;//1
	WorldObj* world;//0
};

