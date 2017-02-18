#include "stdafx.h"
#include "Input.h"
#include <conio.h>
#include <Windows.h>
#include "Soldier.h"

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
	short E = GetKeyState('E') >> 15;

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
		gameplay_functions->add_soldier("soldier",9.6f,100.3f,true);
	}
	if (T) { //Failure check on fake task name
		//gameplay_functions->move_out(player);
		gameplay_functions->play_sound();
	}
	if (E) {
		for (int i = 0; i < 50; i++) {
			std::cout << "Pressed E" << std::endl;
		}
		gameplay_functions->talk(player);
	}
}





