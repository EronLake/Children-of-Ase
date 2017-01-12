#pragma once
#include <string>

class WorldObj
{
public:
	WorldObj();
	WorldObj(int a, int rot, bool col);
	~WorldObj();
private:
	int x;
	int rotation;
	bool collision;
};

class LivingObj :
	public WorldObj
{
public:
	LivingObj();
	LivingObj(int a, int rot, bool col, int b, bool life);
	~LivingObj();
private:
	int health;
	bool alive;
};

class NPC :
	public LivingObj
{
public:
	NPC();
	NPC(int a, int rot, bool col, int b, bool life, int c);
	~NPC();
private:
	int faction;
};

class Soldier :
	public NPC
{
public:
	Soldier();
	Soldier(int a, int rot, bool col, int b, bool life, int c, int d);
	~Soldier();
private:
	int atk;
};

class SplSoldier :
	public Soldier
{
public:
	SplSoldier();
	SplSoldier(int a, int rot, bool col, int b, bool life, int c, int d, int e);
	~SplSoldier();
private:
	int ase;
};

class Hero :
	public SplSoldier
{
public:
	Hero();
	Hero(int a, int rot, bool col, int b, bool life, int c, int d, int e, int f);
	~Hero();
private:
	int affinity;
};

