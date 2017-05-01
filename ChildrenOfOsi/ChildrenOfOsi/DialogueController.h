#pragma once
#include "stdafx.h"
#include "common.h"
#include "Player.h"
#include "DialogueHelper.h"
#include "AIController.h"
#include "PlayerActExecFunctions.h"
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
	static void otherResponse(std::string info, std::string hero_topic);

	static vector<std::vector<std::string>> getOptions();
	static int getOSize() { return options.size(); };
	static vector<std::vector<std::string>> getReplyOptions();

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
	
	static void offerQuest_hack_();

	static DialogueHelper* getDialogueHelper();
	static void add_hero_related_conv_points();
	static void remove_hero_related_conv_points();
	static void replace_all(std::string& str, const std::string& from, const std::string& to);
	static bool offer_quest_on_exit(Hero* hero);
	static void DialogueController::create_farewell();

	static bool prompted_quest;
	static bool accepted_quest;
	
	//used for hero actions
	static bool accepted_action;

	static Action* quest;
	static int scroll_control;

	static Player* player;
	static WorldObj* other;
	static int state;
	static std::string replyString;
	static bool quest_declined;

	//States:
	//0 is no conversation
	//1 is waiting for player input
	//2 is waiting for player response
	//3 is npc conversation point
	//4 is npc response

	static DialogueHelper dialogue;

	static std::vector<std::vector<dialogue_point>> options;
	static std::vector<dialogue_point> replyOptions;
	static std::string message;
	static int optionsIndex;
	static int select;
	static std::vector<int> heroes_player_knows;
};

