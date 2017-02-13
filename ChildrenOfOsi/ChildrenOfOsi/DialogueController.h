#pragma once
#include "stdafx.h"
#include "common.h"

class DialogueController
{
public:
	DialogueController();
	~DialogueController();
	void PlayerConversationPoint();
	void PlayerInform();
	void PlayerResponse();
	void NPCConversationPoint();
	void NPCResponse();

};

