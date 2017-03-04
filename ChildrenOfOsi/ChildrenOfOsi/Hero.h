#pragma once
#include "stdafx.h"
#include "SplSoldier.h"
#include "Relationship.h"
#include "Personality.h"


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
    
    int name;

	void addRelationship(int hero);
};

