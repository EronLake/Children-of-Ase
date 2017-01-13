#pragma once
#include <string>

class WorldObj
{
public:
	WorldObj();
	WorldObj(float x,float y, bool col);
	~WorldObj();
private:
	float xloc;
	float yloc;
	int rotation;
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

