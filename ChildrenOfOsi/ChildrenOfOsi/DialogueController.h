#pragma once
#include "stdafx.h"
#include "common.h"
#include "Player.h"

class DialogueController
{
public:
	DialogueController();
	~DialogueController();
	void PlayerChoose();
	void PlayerConversationPoint(std::string info);
	void PlayerResponse(std::string info);
	void NPCConversationPoint();
	void NPCResponse(std::string info);
	void setPlayer(Player* p);
	void startConversation(NPC* n,bool playerTalk);
	NPC* getNPC();
private:
	Player* player;
	NPC* npc;
	int state;
	//States:
	//0 is no conversation
	//1 is waiting for player input
	//2 is waiting for player response
	//3 is npc conversation point
	//4 is npc response
};

