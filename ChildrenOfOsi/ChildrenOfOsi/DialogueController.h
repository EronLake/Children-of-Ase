#pragma once
#include "stdafx.h"
#include "common.h"
#include "Player.h"
#include "DialogueHelper.h"


class DialogueController
{
public:
	DialogueController();
	~DialogueController();
	static void PlayerChoose();
	static void PlayerConversationPoint(dialogue_point info);
	static void PlayerResponse(dialogue_point info);
	static void otherConversationPoint(dialogue_point info);
	static void otherResponse(dialogue_point info);
	static vector<std::string> getOptions();
	static std::string getMessage() { return message; };
	static void setOptionsIndex(int i) { optionsIndex = i; };
	static void setPlayer(Player* p);
	static void startConversation(WorldObj* n,bool playerTalk);
	static WorldObj* getOther();
	static int getState();
	static void exitDialogue();
private:
	static Player* player;
	static WorldObj* other;
	static int state;
	//States:
	//0 is no conversation
	//1 is waiting for player input
	//2 is waiting for player response
	//3 is npc conversation point
	//4 is npc response
	static DialogueHelper dialogue;
	static dialogue_point options;
	static std::string message;
	static int optionsIndex;
};

