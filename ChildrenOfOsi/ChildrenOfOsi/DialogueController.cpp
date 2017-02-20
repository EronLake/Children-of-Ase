#include "stdafx.h"
#include "DialogueController.h"

Player* DialogueController::player;
WorldObj* DialogueController::other;
int DialogueController::state = 0;
//States:
//0 is no conversation
//1 is waiting for player input
//2 is waiting for player response
//3 is npc conversation point
//4 is npc response
DialogueHelper DialogueController::dialogue;


DialogueController::DialogueController()
{
}


DialogueController::~DialogueController()
{
}

void DialogueController::PlayerChoose()
{
	vector<dialogue_point> options = dialogue.get_possible_conv_pts();
	state = 1;
	//give options to ALex
}

void DialogueController::PlayerConversationPoint(dialogue_point info)
{
	state = 4;
	//dialogue.choose_conv_pt(info);
	//dialogue_point =  call(GUI)
	otherResponse(info);
}

void DialogueController::PlayerResponse(dialogue_point info)
{
	//dialogue.choose_reply_pt(info);
	//dialogue_point =  call(GUI)
	state = 1;
	PlayerChoose();
}

void DialogueController::otherConversationPoint(dialogue_point info)
{
	//dialogue_point point = dialogue.choose_conv_pt(info);

	//std::string sentence = dialogue.gen_dialog(point,hero);
	
	//return sentence 

	state=2;
	//vector<dialogue_point> options = dialogue.get_possible_conv_pts();
	//give options to Alex
}

void DialogueController::otherResponse(dialogue_point info)
{
	//dialogue_point point = dialogue.choose_reply_pt(info);

	//std::string sentence = dialogue.gen_dialog(point,hero);

	//return sentence 


	//dialogue_point response=dialogue.choose_reply_pt(info);
	state = 3;
}

void DialogueController::setPlayer(Player* p)
{
	player = p;
	state = 0;
}

void DialogueController::startConversation(WorldObj* n, bool playerTalk)
{
	for (int i = 0; i < 100; i++) {
		std::cout << player->getName() << " talked with " << n->getName() << std::endl;
	}
	if (playerTalk) {
		PlayerChoose();
	}
	else {
		state = 3;
		otherConversationPoint({"greeting","greeting" });
	}
}

WorldObj* DialogueController::getOther()
{
	return other;
}

int DialogueController::getState()
{
	return state;
}

void DialogueController::exitDialogue()
{
	state=0;
}