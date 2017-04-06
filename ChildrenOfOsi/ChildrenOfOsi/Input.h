#pragma once
#include "stdafx.h"
#include "common.h"
#include "ChildrenOfOsi.h"
#include "DialogueController.h"
#include "GameWindow.h"
#include "RenderHelper.h"
#include "Containers.h"
#include "AIController.h"



class Input
{
private:
	WorldObj* player;
	ChildrenOfOsi* gameplay_functions;
	RenderHelper* rHelper;
	TaskBuffer* tBuffer;
	vector<WorldObj*>* recVec;
	AIController* ai;

	short W;
	short A;
	short S;
	short D;
	short Q;
	short E;
	short F;
	bool disable;
	int count;
	int count2;

	bool prompted_quest = false;

	bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }

public:
	Input(ChildrenOfOsi* _gameplay_functions, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec);
	Input(ChildrenOfOsi* _gameplay_functions, WorldObj * _player, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec, AIController* ai);
	~Input();
	//Region* Desert;
	//Region* Ogun;
	//Region* Mountain;
	//Region* Jungle;
	//Region current_region;
	//Region next_region;

	void InputCheck();

};

