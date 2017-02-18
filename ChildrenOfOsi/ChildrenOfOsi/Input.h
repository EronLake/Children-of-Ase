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
public:
	Input(ChildrenOfOsi* gameplay_function);
	Input(ChildrenOfOsi* gameplay_functions,WorldObj* _player);
	~Input();

	void InputCheck();

};

