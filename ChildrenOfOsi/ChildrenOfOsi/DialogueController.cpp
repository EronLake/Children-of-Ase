#include "stdafx.h"
#include "DialogueController.h"


DialogueController::DialogueController()
{
}


DialogueController::~DialogueController()
{
}

void DialogueController::PlayerChoose()
{
	state = 1;
}

void DialogueController::PlayerConversationPoint(std::string info)
{
	state = 4;
	NPCResponse(info);
}

void DialogueController::PlayerResponse(std::string info)
{
	state = 3;
}

void DialogueController::NPCConversationPoint()
{
	std::string response = "...";//chooseDialogue(npc);
	state=2;
}

void DialogueController::NPCResponse(std::string info)
{
	state = 1;
}

void DialogueController::setPlayer(Player* p)
{
	player = p;
	state = 0;
}

void DialogueController::startConversation(NPC* n, bool playerTalk)
{
	if (playerTalk) {
		PlayerChoose();
	}
	else {
		state = 3;
		NPCConversationPoint();
	}
}

NPC* DialogueController::getNPC()
{
	return npc;
}