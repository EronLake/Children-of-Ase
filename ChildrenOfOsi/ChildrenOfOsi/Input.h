#pragma once
#include "stdafx.h"
#include "common.h"
#include "ChildrenOfOsi.h"
#include "DialogueController.h"



class Input
{
private:
	WorldObj* player;
	ChildrenOfOsi* gameplay_functions;

	short W;
	short A;
	short S;
	short D;
	short Q;
	short E;

public:
	Input(ChildrenOfOsi* gameplay_function);
	Input(ChildrenOfOsi* gameplay_functions,WorldObj* _player);
	~Input();

	void InputCheck();

};

