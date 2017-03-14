#pragma once
#include "stdafx.h"
#include "SplSoldier.h"
#include "Relationship.h"
#include "Personality.h"
#include "Memory.h"

class ActionPool;
class Party;

class Hero :
	public SplSoldier
{
public:
	
	Hero();
	Hero(int name, float x, float y, bool col);
	Hero(int name, Vector2f p_topLeft, float p_width, float p_height);
	~Hero();

	unordered_map<int, Relationship*> rel;
	Personality* traits;
	//Planner* planner;
	ActionPool* actionPool;
    int name;

	int mem_counter;
	vector<Memory*> memories;

	Party* cur_party;
	virtual void defeat();
	void kill();

	bool incapacitated;

	void addRelationship(int hero);
	void Hero::setPersonality(int a, int k, int h, int p, int r, int e, int g);
};

