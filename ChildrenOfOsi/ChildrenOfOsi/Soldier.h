#pragma once
#include "NPC.h"
#include "stdafx.h"
#include "Attack.h"
#include "Containers.h"

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
	void setPatrol(bool p) { patrol=p; };
	bool getPatrol() { return patrol; };
	Attack* melee;
	vector<Attack*>atkType;
	unordered_map<Attack*,int> cdMap;
	void addAttackType(Attack* a);
	void newAttack(int i, Attack* a);
	void meleeAttack();
	void setCD(int c) { cdTotal = c; };
	int getCD() { return cdTotal; };
	void updateCD();
	int timeCD() { return cdTime; };
	void setCool(bool c) { cool = c; };
	bool getCool() { return cool; };
	bool getCool(int c);
	void setParty(Party* p) { party=p; };
	Party* getParty() { return party; };
	int getInstances() { return instances; };
	std::string getKey() { return key; };
	std::string getAtKey() { return atkey="Soldier" + std::to_string(getID()) + "_" + std::to_string(atkType.size()) + "_" + std::to_string(instances); };

private:
	Party* party;
	bool inCombat;
	bool evade;
	bool holdPos;
	bool patrol;
	int cdTotal;
	int cdTime;
	bool cool;
	int instances;
	std::string key;
	std::string atkey;
};

