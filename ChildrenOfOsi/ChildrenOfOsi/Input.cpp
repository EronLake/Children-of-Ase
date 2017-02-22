#include "stdafx.h"
#include "Input.h"
#include <conio.h>
#include <Windows.h>
#include "Soldier.h"
#include "json.h"

Input::Input(ChildrenOfOsi* _gameplay_functions)
{
	disable = false;
	count = 0;
	gameplay_functions = _gameplay_functions;
	LOG("Input Objected Constructed");
}

Input::Input(ChildrenOfOsi* _gameplay_functions, WorldObj * _player)
{
	disable = false;
	count = 0;
	gameplay_functions = _gameplay_functions;
	gameplay_functions->play_sound("Play");
	gameplay_functions->play_sound("Walk");
	gameplay_functions->play_sound("Pause");
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
	short ENTER = GetKeyState('\n') >> 15;
	short V = GetKeyState('V') >> 15;

	if (DialogueController::getState() == 0) {

		if (W)                //Moving up
		{
			gameplay_functions->play_sound("Unpause");
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
			gameplay_functions->play_sound("Unpause");
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
			gameplay_functions->play_sound("Unpause");
			gameplay_functions->move_left(player);
		}
		else if (D)        //Only moving right
		{
			gameplay_functions->play_sound("Unpause");
			gameplay_functions->move_right(player);
		}
		else {
			gameplay_functions->play_sound("Pause");
		}

		if (!(W || A || S || D))  // No movement keys pressed
		{
			//Set texture to idle
			gameplay_functions->stop(player);
		}

		if (E) {
			std::cout << "Pressed E" << std::endl;
			gameplay_functions->talk(player);
		}

		if (L) {
			std::string image_name;
			std::string obj_name;

			std::cout << "Pressed Enter" << std::endl;
			std::cout << "INPUT FILE NAME " << std::endl;
			std::cout << "///////////////////////////////" << std::endl;
			std::cin >> image_name;
			std::cout << "INPUT OBJECT NAME " << std::endl;
			std::cout << "///////////////////////////////" << std::endl;
			std::cin >> obj_name;
			std::cout << image_name << ": "<<  player->getX() << ":" << player->getY() << std::endl;


			Json::Value root;
			Json::Reader reader;

			std::ifstream in_file("config.json");
			in_file >> root;
			in_file.close();

			std::ofstream file;
			file.open("config.json");


			//populate 'value_obj' with the objects, arrays etc.
			Json::Value new_obj = {};

			new_obj["x"] = floor(player->getX()/100);
			new_obj["y"] = floor(player->getY()/100);

			new_obj["hight"] = 400.0;
			new_obj["width"] = 600.0;

			new_obj["frame_num"] = 1;

			new_obj["name"] = obj_name;
			new_obj["tex_file"] = "Assets/Sprites/" + image_name + ".png";
			
		
			root[obj_name] = new_obj;

			Json::StyledWriter styledWriter;
			file << styledWriter.write(root);

			file.close();

			system("PAUSE");
			
			
		}

	}
	
	if (DialogueController::getState() > 0) {
		if (Q) {
			DialogueController::exitDialogue();
		}
		if (H) {
			DialogueController::setOptionsIndex(0);
			gameplay_functions->setSwordGlow(player);
		}
		if (J) {
			DialogueController::setOptionsIndex(1);
			gameplay_functions->setHeartGlow(player);
		}
		if (K) {
			DialogueController::setOptionsIndex(2);
			gameplay_functions->setFaceGlow(player);
		}
		if (L) {
			DialogueController::setOptionsIndex(3);
			gameplay_functions->setQuestionGlow(player);
		}
		if (count == 60) {
			disable = false;
			count = 0;
		}
		if (!disable) {
			if (W && DialogueController::getState() == 1) {
				int tmp = DialogueController::getOptionsIndex();
				if (tmp > 0) {
					DialogueController::setOptionsIndex(--tmp);
					disable = true;
					std::cout << "OptionsIndex: " << tmp << std::endl;
					switch (DialogueController::getOptionsIndex()) {
					case 0: gameplay_functions->setSwordGlow(player);
					case 1: gameplay_functions->setHeartGlow(player);
					case 2: gameplay_functions->setFaceGlow(player);
					case 3: gameplay_functions->setQuestionGlow(player);
					}
				}
			}
			if (S && DialogueController::getState() == 1) {
				int tmp = DialogueController::getOptionsIndex();
				if (tmp < DialogueController::getOSize() - 1) {
					DialogueController::setOptionsIndex(++tmp);
					disable = true;
					std::cout << "OptionsIndex: " << tmp << std::endl;
					switch (DialogueController::getOptionsIndex()) {
					case 0: gameplay_functions->setSwordGlow(player);
					case 1: gameplay_functions->setHeartGlow(player);
					case 2: gameplay_functions->setFaceGlow(player);
					case 3: gameplay_functions->setQuestionGlow(player);
					}
				}
			}
			if (D && DialogueController::getState() < 3) {
				int tmp = DialogueController::getSelect();
				if (DialogueController::getState() == 1) {
					if (tmp < (DialogueController::getOptions().size() - 1)) {
						DialogueController::setSelect(++tmp);
						disable = true;
						std::cout << "Index: " << tmp << std::endl;
					}
					if (tmp > (DialogueController::getReplyOptions().size() - 1)) {
						tmp = 0;
						DialogueController::setSelect(tmp);
						disable = true;
						std::cout << "Index: " << tmp << std::endl;
					}
				}
				if (DialogueController::getState() == 2) {
					if (tmp < (DialogueController::getReplyOptions().size() - 1)) {
						DialogueController::setSelect(++tmp);
						disable = true;
						std::cout << "Index: " << tmp << std::endl;
					}
					if (tmp > (DialogueController::getReplyOptions().size() - 1)) {
						tmp = 0;
						DialogueController::setSelect(tmp);
						disable = true;
						std::cout << "Index: " << tmp << std::endl;
					}
				}
			}
			if (A && DialogueController::getState() < 3) {
				int tmp = DialogueController::getSelect();
				if (tmp > 0) {
					DialogueController::setSelect(--tmp);
					disable = true;
					std::cout << "Index: " << tmp << std::endl;
				}
			}
			if (V) {
				std::cout << "ENTER" << std::endl;
				if (DialogueController::getState() == 1) {
					disable = true;
					DialogueController::PlayerConversationPoint();
				}
				else if (DialogueController::getState() == 2) {
					disable = true;
					DialogueController::PlayerResponse();
				}
			}
		}
		else {
			count++;
		}
	}
}





