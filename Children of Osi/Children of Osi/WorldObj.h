#pragma once
#include <string>
#include "Vector2f.h"

class WorldObj
{
public:
	WorldObj();
	WorldObj(float x,float y, bool col);
	~WorldObj();
	void setLoc(Vector2f l);
	Vector2f getLoc();
	void setRot(Vector2f r);
	Vector2f getRot();
	void setCollision(bool c);
	bool getCollision();
private:
	Vector2f loc;
	Vector2f rotation;
	bool collision;
};

class LivingObj :
	public WorldObj
{
public:
	LivingObj();
	LivingObj(float x, float y, bool col);
	~LivingObj();
	int getHealth();
	void setHealth(int h);
	bool getAlive();
	void setAlive(bool v);
private:
	int health;
	bool alive;
};

class NPC :
	public LivingObj
{
public:
	NPC();
	NPC(float x, float y, bool col);
	~NPC();
private:
	int faction;
};

class Soldier :
	public NPC
{
public:
	Soldier();
	Soldier(float x, float y, bool col);
	~Soldier();
	int getAtk();
	void setAtk(int a);
private:
	int atk;
};

class SplSoldier :
	public Soldier
{
public:
	SplSoldier();
	SplSoldier(float x, float y, bool col);
	~SplSoldier();
	int getAse();
	void setAse(int a);
private:
	int ase;
};

class Hero :
	public SplSoldier
{
public:
	Hero();
	Hero(float x, float y, bool col);
	~Hero();
private:
	int affinity;
};

