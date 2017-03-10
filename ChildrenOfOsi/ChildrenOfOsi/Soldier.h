#pragma once
#include "NPC.h"
#include "stdafx.h"
#include "Attack.h"

class Party;

class Soldier :
	public NPC
{
public:
	Soldier();
	Soldier(float x, float y, bool col);
	Soldier(Vector2f p_topLeft, float p_width, float p_height);
	~Soldier();
	void setInCombat(bool c) { inCombat = c; };
	bool getInCombat() { return inCombat; };
	void setEvade(bool e) { evade = e; };
	bool getEvade() { return evade; };
	void setHold(bool h) {holdPos = h; };
	bool getHold() { return holdPos; };
	Attack melee;
	vector<Attack*>atkType;
	vector<Attack*>available;
	unordered_map<Attack*,int> cdMap;
	Attack* newAttack(int i);
	Attack* meleeAttack();
	void setCD(int c) { cdTotal = c; };
	int getCD() { return cdTotal; };
	void updateCD();
	int framesCD() { return cdFrame; };
	void setCool(bool c) { cool = c; };
	bool getCool() { return cool; };
	void setParty(Party* p) { party=p; };
	bool getParty() { return party; };
private:
	Party* party;
	bool inCombat;
	bool evade;
	bool holdPos;
	int cdTotal;
	int cdFrame;
	bool cool;
};

