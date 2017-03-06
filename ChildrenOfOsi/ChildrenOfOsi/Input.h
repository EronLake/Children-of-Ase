#pragma once
#include "stdafx.h"
#include "common.h"
#include "ChildrenOfOsi.h"
#include "DialogueController.h"
#include "GameWindow.h"
#include "RenderHelper.h"
#include "Containers.h"



class Input
{
private:
	WorldObj* player;
	ChildrenOfOsi* gameplay_functions;
	RenderHelper* rHelper;
	TaskBuffer* tBuffer;
	vector<WorldObj*>* recVec;

	short W;
	short A;
	short S;
	short D;
	short Q;
	short E;
	short F;
	bool disable;
	int count;

	bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }

public:
	Input(ChildrenOfOsi* _gameplay_functions, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec);
	Input(ChildrenOfOsi* _gameplay_functions, WorldObj * _player, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec);
	~Input();

	void InputCheck();

};

