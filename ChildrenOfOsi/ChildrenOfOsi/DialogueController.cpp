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
dialogue_point DialogueController::options;
std::string DialogueController::message;
int DialogueController::optionsIndex=0;


DialogueController::DialogueController()
{
}


DialogueController::~DialogueController()
{
}

void DialogueController::PlayerChoose()
{
	//options = dialogue.get_possible_conv_pts();
	state = 1;
	optionsIndex = 0;
	getOptions();
	//give option to Alex
}

void DialogueController::PlayerConversationPoint(dialogue_point info)
{
	state = 4;
	dialogue.choose_conv_pt(info);
	otherResponse(info);
}

void DialogueController::PlayerResponse(dialogue_point info)
{
	dialogue.choose_reply_pt(info);
	state = 1;
	PlayerChoose();
}

void DialogueController::otherConversationPoint()
{
	//dialogue_point line = dialogue.choose_reply_pt();
	//options = dialogue.get_possible_reply_pts();
	state = 2;
	optionsIndex = 0;
	getOptions();
	//give info to Alex
}

void DialogueController::otherResponse(dialogue_point info)
{
	dialogue_point line=dialogue.choose_reply_pt(info);
	state = 3;
}

vector<std::string> DialogueController::getOptions()
{
	vector<std::string> tmp;
	if (options.size() > 2 * optionsIndex) {
		tmp.push_back(options[2 * optionsIndex]);
	}
	if (options.size() > 2 * optionsIndex +1) {
		tmp.push_back(options[2 * optionsIndex + 1]);
	}
	return tmp;
	//give tmp to Alex
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
		otherConversationPoint();
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
	other = nullptr;
	state=0;
}