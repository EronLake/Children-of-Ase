#pragma once
#include "stdafx.h"
#include "common.h"
#include "Player.h"

class Alliance;

class Village
{
public:
	Village();
	~Village();
	Alliance* alliance;
	vector<NPC*> members;
	void setStatus(std::string s) { status = s; };
	std::string getStatus() { return status; };
	Village* conquerer;
	vector<Village*> conquered;
	Hero* leader;
private:
	std::string status;
};

