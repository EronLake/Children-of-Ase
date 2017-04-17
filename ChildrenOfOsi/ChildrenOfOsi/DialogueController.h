#pragma once
#include "stdafx.h"
#include "common.h"
#include "Player.h"
#include "DialogueHelper.h"
#include "AIController.h"
#include "Party.h"

class DialogueController
{
public:
	DialogueController();
	~DialogueController();
	static void PlayerChoose();

	static void PlayerConversationPoint();
	static void PlayerResponse();
	static void otherConversationPoint(dialogue_point line);
	static void otherResponse(std::string info);

	static vector<std::string> getOptions();
	static int getOSize() { return options.size(); };
	static vector<std::string> getReplyOptions();

	static std::string getMessage() { return message; };
	static void setOptionsIndex(int i) { optionsIndex = i; select = 0; };
	static int getOptionsIndex() { return optionsIndex; };
	static void setSelect(int i) { select = i; };
	static int getSelect() { return select; };
	static void setPlayer(Player* p);
	static void startConversation(WorldObj* n, bool playerTalk);
	static WorldObj* getOther();
	static int getState();
	static void exitDialogue();
	static void setAI(AIController* ai_c) { ai = ai_c; }
	static void set_scroll_control(int scroll_int);
	
	static void offerQuest_hack_();

	static DialogueHelper* getDialogueHelper();
	static std::string convert_option_to_phrase(std::string opt);

	static bool prompted_quest;
	static bool accepted_quest;

	static Action* quest;
	static int scroll_control;
//private:
	static Player* player;
	static WorldObj* other;
	static int state;
	static std::string replyString;
	//States:
	//0 is no conversation
	//1 is waiting for player input
	//2 is waiting for player response
	//3 is npc conversation point
	//4 is npc response
	static DialogueHelper dialogue;
	static AIController* ai;
	static std::vector<std::vector<dialogue_point>> options;
	static std::vector<dialogue_point> replyOptions;
	static std::string message;
	static int optionsIndex;
	static int select;
	
};

