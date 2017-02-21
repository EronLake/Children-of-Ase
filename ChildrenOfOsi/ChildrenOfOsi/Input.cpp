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
	short W = GetKeyState('W') >> 15;
	short A = GetKeyState('A') >> 15;
	short S = GetKeyState('S') >> 15;
	short D = GetKeyState('D') >> 15;
	short R = GetKeyState('R') >> 15;
	short T = GetKeyState('T') >> 15;
	short E = GetKeyState('E') >> 15;
	short Q = GetKeyState('Q') >> 15;
	short H = GetKeyState('H') >> 15;
	short J = GetKeyState('J') >> 15;
	short K = GetKeyState('K') >> 15;
	short L = GetKeyState('L') >> 15;

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
			gameplay_functions->stop(player);
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
		if (H) {
			gameplay_functions->setSwordGlow(player);
		}
		if (J) {
			gameplay_functions->setHeartGlow(player);
		}
		if (K) {
			gameplay_functions->setFaceGlow(player);
		}
		if (L) {
			gameplay_functions->setQuestionGlow(player);
		}
	}
}





