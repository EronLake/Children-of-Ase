#pragma once
#include "stdafx.h"
#include "SplSoldier.h"
#include "Relationship.h"


class Hero :
	public SplSoldier
{
public:
	int name;
	Hero();
	Hero(int name, float x, float y, bool col);
	Hero(int name, Vector2f p_topLeft, float p_width, float p_height);
	~Hero();
	void addRelation(int p_heroNum, Relationship* p_relations);
	void removeRelation(int p_heroNum);
	Relationship* getRelation(int p_heroNum);
private:
	int affinity;
	std::unordered_map<int, Relationship*> relationMap;
};

