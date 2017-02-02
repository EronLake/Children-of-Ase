#include "stdafx.h"
#include "Input.h"
#include <conio.h>
#include <Windows.h>

Input::Input(ChildrenOfOsi* _gameplay_functions)
{
	gameplay_functions = _gameplay_functions;
	LOG("Input Objected Constructed");
}

Input::Input(ChildrenOfOsi* _gameplay_functions, WorldObj * _player)
{
	gameplay_functions = _gameplay_functions;
	player = _player;
	LOG("Input Object W/Player Constructed");
}


Input::~Input()
{
	LOG("Input Objected Destroyed");
}

void Input::InputCheck()
{
	short W = GetKeyState('W') >> 15;
	short A = GetKeyState('A') >> 15;
	short S = GetKeyState('S') >> 15;
	short D = GetKeyState('D') >> 15;
	short R = GetKeyState('R') >> 15;
	short T = GetKeyState('T') >> 15;

	if (W)
	{
		gameplay_functions->move_up(player);
	}
	if (A)
	{
		gameplay_functions->move_left(player);
	}
	if (S)
	{
		gameplay_functions->move_down(player);
	}
	if (D)
	{
		gameplay_functions->move_right(player);
	}
	if (R) {
//      Soldier* soldier;
//		create("Create_Soldier", "MODIFY_POOL", soldier, ... );
	}
	if (T) { //Failure check on fake task name
		gameplay_functions->move_out(player);
	}
}





