#pragma once
#include "stdafx.h"
#include "common.h"
#include "ChildrenOfOsi.h"
#include "DialogueController.h"
#include "GameWindow.h"
#include "RenderHelper.h"



class Input
{
private:
	WorldObj* player;
	ChildrenOfOsi* gameplay_functions;
	RenderHelper* rHelper;

	short W;
	short A;
	short S;
	short D;
	short Q;
	short E;
	short F;
	bool disable;
	int count;

public:
	Input(ChildrenOfOsi* gameplay_function, RenderHelper* rHelper);
	Input(ChildrenOfOsi* gameplay_functions,WorldObj* _player, RenderHelper* rHelper);
	~Input();

	void InputCheck();

};

