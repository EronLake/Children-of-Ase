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
	gameplay_functions->play_sound("Play");
	player = _player;
	LOG("Input Object W/Player Constructed");
}


Input::~Input()
{
	LOG("Input Objected Destroyed");
}

void Input::InputCheck()
{
	W = GetKeyState('W') >> 15;
	A = GetKeyState('A') >> 15;
	S = GetKeyState('S') >> 15;
	D = GetKeyState('D') >> 15;
	E = GetKeyState('E') >> 15;
	Q = GetKeyState('Q') >> 15;

	if (DialogueController::getState() == 0) {

		if (W)                //Moving up
		{
			if (A) {          //Moving up and left
				gameplay_functions->move_up_left(player);   
			}
			else if (D) {     //Moving up and right
				gameplay_functions->move_up_right(player);
			}
			else {
				gameplay_functions->move_up(player);
			}
		}
		else if (S)          //Moving down
		{ 
			if (A) {         //Moving down and left
				gameplay_functions->move_down_left(player);
			}
			else if (D) {    //Moving down and right
				gameplay_functions->move_down_right(player);
			}
			else {
			    gameplay_functions->move_down(player);
			} 
		}
		else if (A) {      //Only moving left
			gameplay_functions->move_left(player);
		}
		else if (D)        //Only moving right
		{
			gameplay_functions->move_right(player);
		}

		if (!(W || A || S || D))  // No movement keys pressed
		{
			//Set texture to idle
		}

		if (E) {
			for (int i = 0; i < 50; i++) {
				std::cout << "Pressed E" << std::endl;
			}
			gameplay_functions->talk(player);
		}

	}
	
	if (DialogueController::getState() > 0) {
		if (Q) {
			DialogueController::exitDialogue();
		}
	}
}





