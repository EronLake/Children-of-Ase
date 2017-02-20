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
	//getOptions();
	//give option to Alex
}

void DialogueController::PlayerConversationPoint(int info)
{
	state = 4;
	//dialogue.choose_conv_pt(info);
	std::string choice = options[2 * optionsIndex + info];
	otherResponse(choice);
}

void DialogueController::PlayerResponse(int info)
{
	state = 1;
	std::string choice = options[2 * optionsIndex + info];
	//dialogue.choose_reply_pt(info);
	PlayerChoose();
}

void DialogueController::otherConversationPoint()
{
	//message += "\n"+"\n"+dialogue.choose_reply_pt();
	//options = dialogue.get_possible_reply_pts();
	state = 2;
	optionsIndex = 0;
	//getOptions();
	//give info to Alex
}

void DialogueController::otherResponse(std::string info)
{
	//dialogue_point line=dialogue.choose_reply_pt(info);
	state = 3;
	otherConversationPoint();
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
	other = n;
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