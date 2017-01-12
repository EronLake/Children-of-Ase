#pragma once

class WorldObj
{
public:
	WorldObj();
	WorldObj(int a);
	~WorldObj();
private:
	int x;
};

class LivingObj :
	public WorldObj
{
public:
	LivingObj();
	LivingObj(int a,int b);
	~LivingObj();
private:
	int health;
};

class NPC :
	public LivingObj
{
public:
	NPC();
	NPC(int a, int b, int c);
	~NPC();
private:
	int faction;
};

class Soldier :
	public NPC
{
public:
	Soldier();
	Soldier(int a, int b, int c, int d);
	~Soldier();
private:
	int atk;
};

class SplSoldier :
	public Soldier
{
public:
	SplSoldier();
	SplSoldier(int a, int b, int c, int d, int e);
	~SplSoldier();
private:
	int ase;
};

class Hero :
	public SplSoldier
{
public:
	Hero();
	Hero(int a, int b, int c, int d, int e, int f);
	~Hero();
private:
	int affinity;
};

