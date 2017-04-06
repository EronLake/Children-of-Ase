#include "stdafx.h"
#include "Input.h"
#include <conio.h>
#include <Windows.h>
#include "Soldier.h"
#include "Attack.h"
#include "CheckClass.h"
#include "json.h"


Input::Input(ChildrenOfOsi* _gameplay_functions, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec)
{
	disable = false;
	count = 0;
	gameplay_functions = _gameplay_functions;
	rHelper = _rHelper;
	tBuffer = _tBuffer;
	recVec = _recVec;
	LOG("Input Objected Constructed");
}

Input::Input(ChildrenOfOsi* _gameplay_functions, WorldObj * _player, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec, AIController* ai_c)
{
	disable = false;
	count = 0;
	count2 = 0;
	gameplay_functions = _gameplay_functions;
	rHelper = _rHelper;
	tBuffer = _tBuffer;
	recVec = _recVec;
	ai = ai_c;

	//gameplay_functions->play_sound("Play");
	//gameplay_functions->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav");
	//gameplay_functions->play_sound("Walk");
	//gameplay_functions->pause_unpause("Pause", "walk_loop.wav");
	//gameplay_functions->play_sound("Pause");
	//gameplay_functions->play_sound("Sixers");
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
	short ENTER = GetKeyState(VK_RETURN) >> 15;
	short SHIFT = GetKeyState(VK_LSHIFT) >> 15;
	short V = GetKeyState('V') >> 15;
	short F = GetKeyState('F') >> 15;
	short P = GetKeyState('P') >> 15;
	short Z = GetKeyState('Z') >> 15;
	short G = GetKeyState('G') >> 15;
	short Y = GetKeyState('Y') >> 15;
	short U = GetKeyState('U') >> 15;


	if (DialogueController::getState() == 0) {
		Player* t = CheckClass::isPlayer(player);
		gameplay_functions->combat(player);
		if (SHIFT) {
				t->setSpeed(15);
		}
		else {
			t->setSpeed(8);
		}
		if (W)                //Moving up
		{
			//gameplay_functions->pause_unpause("Unpause","walk_loop.wav");
			
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
			//gameplay_functions->pause_unpause("Unpause", "walk_loop.wav");
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
			//gameplay_functions->pause_unpause("Unpause", "walk_loop.wav");
			gameplay_functions->move_left(player);
		}
		else if (D)        //Only moving right
		{
			//gameplay_functions->pause_unpause("Unpause", "walk_loop.wav");
			gameplay_functions->move_right(player);
		}
		else {
			//gameplay_functions->pause_unpause("Pause", "walk_loop.wav");
		}

		if (!(W || A || S || D))  // No movement keys pressed
		{
			//Set texture to idle
			gameplay_functions->stop(player);
		}

		if (E) {
			////std::cout << "Pressed E" << std::endl;
			gameplay_functions->talk(player);
		}
		if ((W||A||S||D) && F) {
			if (t->getCool()) {
				////std::cout << "Pressed Moving F" << std::endl;
				t->flipSwing();
				t->meleeAttack();
				gameplay_functions->melee(t);
			}
		}
		 else if (F) {
			if (t) {
					if (t->getCool()) {
						////std::cout << "Pressed F" << std::endl;
						t->meleeAttack();
						gameplay_functions->melee(t);
					}
					else if (t->getCombo()) {
						////std::cout << "COMBO" << std::endl;
						t->sprite.unlockAnimation();
						t->resetCD();
						if (t->getCool()) {
							////std::cout << "Pressed F" << std::endl;
							t->flipSwing();
							t->meleeAttack();
							gameplay_functions->melee(t);
						} else {
							t->sprite.lockAnimation();
						}
					} 
			}
		}
		else if (R && SHIFT) {
			if (t) {
				if (t->getCool(1)) {
					////std::cout << "Pressed Shift+R" << std::endl;
					gameplay_functions->special(t, 1);
					gameplay_functions->fire(t);
				}
			}
		} else if (R) {
				if (t) {
					if (t->getCool(0)) {
						////std::cout << "Pressed R" << std::endl;
						gameplay_functions->special(t,0);
						gameplay_functions->melee(t);
					}
				}
		} else if (T) {
				if (t) {
					if (t->getCool(2)) {
						////std::cout << "Pressed T" << std::endl;
						//t->meleeAttack();
						//gameplay_functions->melee(t);
						//t->resetCD(2);
						gameplay_functions->special(t, 2);
						gameplay_functions->spin(t);
					}
				}
		}
		float firstOld = 0;
		float secondOld = 0;
		if (P) {
			////std::cout << player->getX() << " " << player->getY() << std::endl;
			std::ofstream rivFile;
			rivFile.open("rivLines.txt", std::ios_base::app);
			rivFile << firstOld << " " << secondOld << ", ";
			rivFile << player->getX() << " " << player->getY()+player->getHeight() << std::endl;
			firstOld = player->getX();
			secondOld = player->getY() + player->getHeight();
			rivFile.close();
			//std::system("PAUSE");
		}
		if (Z) {
			std::ofstream rivFile;
			rivFile.open("rivLines.txt", std::ios_base::app);
			rivFile << std::endl;
			rivFile << std::endl;
			rivFile << std::endl;
			rivFile.close();
		} 
		if (G) {
			t->getParty()->set_defend(t->getLoc());
			t->getParty()->setMode(Party::MODE_DEFEND);
		}
		if (Y) {
			t->getParty()->setMode(Party::MODE_ATTACK);
		}
		if (U) {
			t->getParty()->setMode(Party::MODE_FLEE);
		}
		if (H) {
			t->getParty()->set_home(t->getLoc());
		}
		if (L) {
			t->getParty()->clear_patrol_route();
		}
		if (count2 > 0)count2--;
		if (V && (count2==0)) {
			t->getParty()->add_patrol_loc(t->getLoc());
			count2 = 200;
		}
		if (J && (count2 == 0)) {
			t->getParty()->setMode(Party::MODE_FLEE);
			t->getParty()->removeSoldier(t);
			count2 = 200;
		}
		if (K && (count2 == 0)) {
			t->getParty()->setMode(Party::MODE_PATROL);
			t->getParty()->removeSoldier(t);
			count2 = 200;
		}
		/*
		if (L) {
		std::string image_name;
		std::string obj_name;

		////std::cout << "Pressed Enter" << std::endl;
		////std::cout << "INPUT FILE NAME " << std::endl;
		////std::cout << "///////////////////////////////" << std::endl;
		std::cin >> image_name;
		////std::cout << "INPUT OBJECT NAME " << std::endl;
		////std::cout << "///////////////////////////////" << std::endl;
		std::cin >> obj_name;
		////std::cout << image_name << ": " << player->getX() << ":" << player->getY() << std::endl;


		Json::Value root;
		Json::Reader reader;

		std::ifstream in_file("config.json");
		in_file >> root;
		in_file.close();

		std::ofstream file;
		file.open("config.json");


		//populate 'value_obj' with the objects, arrays etc.
		Json::Value new_obj = {};

		new_obj["x"] = floor(player->getX() / 100);
		new_obj["y"] = floor(player->getY() / 100);

		new_obj["hight"] = 400.0;
		new_obj["width"] = 600.0;

		new_obj["frame_num"] = 1;

		new_obj["name"] = obj_name;
		new_obj["tex_file"] = image_name;

		new_obj["bodyx1"] = 110;
		new_obj["bodyx2"] = 150;
		new_obj["bodyy1"] = 120;
		new_obj["bodyy2"] = 60;


		root[obj_name] = new_obj;

		Json::StyledWriter styledWriter;
		file << styledWriter.write(root);

		file.close();

		system("PAUSE");


		}
		*/
		
		
		if (L && (GetKeyState(VK_LBUTTON) & 0x100) == 0)
		{
			std::string image_name;
			std::string obj_name;
			int frame_num;
			int offsetleft;
			int offsety;


			std::cout << "Pressed Enter" << std::endl;
			std::cout << "INPUT FILE NAME " << std::endl;
			std::cout << "///////////////////////////////" << std::endl;
			std::cin >> image_name;
			std::cout << "INPUT FRAME NUMBER(PROBABLY 1) " << std::endl;
			std::cout << "///////////////////////////////" << std::endl;
			std::cin >> frame_num;
			std::cout << image_name << ": " << player->getX() << ":" << player->getY() << std::endl;
			std::cout << "INPUT OBJECT NAME " << std::endl;
			std::cout << "///////////////////////////////" << std::endl;
			std::cin >> obj_name;
			std::cout << image_name << ": " << player->getX() << ":" << player->getY() << std::endl;

			if (Containers::texture_table[image_name]) {
				////cout << image_name << "Already in Table /////////////////////////////" << endl;
			}
			else
			{
				////cout << image_name << "Not in Table /////////////////////////////" << endl;
				gameplay_functions->add_texture(image_name, 0, 0, 0);

				//set file takes up memory
				tBuffer->run();
				Containers::texture_table[image_name]->setFile("Assets/Sprites/" + image_name + ".png", frame_num);

			}

			gameplay_functions->add_worldObj(obj_name, (player->getX()) + 20, (player->getY()) + 20, true);

			tBuffer->run();

			Containers::worldObj_table[obj_name]->setWidth(500);
			Containers::worldObj_table[obj_name]->setHeight(500);

			Containers::worldObj_table[obj_name]->sprite.setTexture(Containers::texture_table[image_name]);
			Containers::worldObj_table[obj_name]->setInteractable(false);
			Containers::worldObj_table[obj_name]->offsetBody(0, 0, 0, 0, 0);

			recVec->push_back(Containers::worldObj_table[obj_name]);


			//this adds the object to the config file
			Json::Value root;
			Json::Reader reader;

			std::ifstream in_file("config.json");
			in_file >> root;
			in_file.close();

			std::ofstream file;
			file.open("config.json");


			//populate 'value_obj' with the objects, arrays etc.
			Json::Value new_obj = {};

			new_obj["x"] = floor(player->getX() / 100); new_obj["y"] = floor(player->getY() / 100);
			new_obj["hight"] = 500; new_obj["width"] = 500;
			new_obj["frame_num"] = frame_num;
			new_obj["name"] = obj_name; new_obj["tex_file"] = image_name;
			new_obj["bodyx1"] = 0; new_obj["bodyx2"] = 0; new_obj["bodyy1"] = 0; new_obj["bodyy2"] = 0;

			root[obj_name] = new_obj;

			Json::StyledWriter styledWriter;
			file << styledWriter.write(root);

			file.close();


			system("PAUSE");

		}

		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
		{
			/*POINT p;
			if (ScreenToClient(window, &p))
			{
			////cout << "////////////////////////" << endl;
			////cout << p.x << p.y << endl;
			////cout << "////////////////////////" << endl;
			}*/

			double xpos;
			double ypos;
			glfwGetCursorPos(GameWindow::window, &xpos, &ypos);

			double mouseX = rHelper->camera->getX() + xpos * GameWindow::WINDOW_WIDTH_DP / 1300;
			double mouseY = rHelper->camera->getY() + ypos * GameWindow::WINDOW_HEIGHT_DP / 700;

			std::cout << "////////////////////////" << endl;
			std::cout << xpos << ":" << ypos << endl;
			std::cout << "X: " << xpos << endl;
			std::cout << "Y: " << ypos << endl;
			std::cout << "////////////////////////" << endl;

			bool xCollide;
			bool yCollide;

			std::string collide_with = "";

			for (auto itr = Containers::worldObj_table.begin(); itr != Containers::worldObj_table.end(); itr++)
			{
				//for (int i = 0; i < itr->second->size(); i++) {
				xCollide = coordOverlap(itr->second->getX(), mouseX, mouseX) || coordOverlap(mouseX, itr->second->getX(), itr->second->getX() + itr->second->getWidth());
				yCollide = coordOverlap(itr->second->getY(), mouseY, mouseY) || coordOverlap(mouseY, itr->second->getY(), itr->second->getY() + itr->second->getHeight());
				if (xCollide && yCollide)
				{
					collide_with = itr->first;
					std::cout << "////////////////////////" << endl;
					std::cout << "COLLIDED WITH: " << collide_with << endl;
					std::cout << "////////////////////////" << endl;

					//float diffX = Containers::worldObj_table[collide_with]->body[i].getX() - Containers::worldObj_table[collide_with]->getX();
					//float diffY = Containers::worldObj_table[collide_with]->body[i].getY() - Containers::worldObj_table[collide_with]->getY();

					//Containers::worldObj_table[collide_with]->body[i].setX(mouseX - Containers::worldObj_table[collide_with]->body[i].getWidth());
					//Containers::worldObj_table[collide_with]->body[i].setY(mouseY - Containers::worldObj_table[collide_with]->body[i].getHeight());

				}
				//}
			}

			if (collide_with != "")
			{
				Containers::worldObj_table[collide_with]->setX(mouseX - (Containers::worldObj_table[collide_with]->getWidth()) / 2);
				Containers::worldObj_table[collide_with]->setY(mouseY - (Containers::worldObj_table[collide_with]->getHeight()) / 2);

				int body_number = 0;
				float left;
				float right;
				float top;
				float bottom;

				if (L)
				{
					std::cout << "////////////////////////" << endl;
					std::cout << "ENTER NAME OF THE VARIABLE YOU WOULD LIKE TO CHANGE: ";

					string variable_for_change;
					cin >> variable_for_change;

					if (variable_for_change == "width")
					{
						std::cout << "////////////////////////" << endl;
						std::cout << "ENTER WIDTH AS FLOAT: ";

						float value_to_change_to;
						cin >> value_to_change_to;

						Containers::worldObj_table[collide_with]->setWidth(value_to_change_to);
					}
					else if (variable_for_change == "height")
					{
						std::cout << "////////////////////////" << endl;
						std::cout << "ENTER HEIGHT AS FLOAT: ";

						float value_to_change_to;
						cin >> value_to_change_to;

						Containers::worldObj_table[collide_with]->setHeight(value_to_change_to);
					}

					if (variable_for_change == "size")
					{
						std::cout << "////////////////////////" << endl;
						std::cout << "ENTER SIZE AS FLOAT: ";

						float value_to_change_to;
						cin >> value_to_change_to;

						Containers::worldObj_table[collide_with]->setWidth(value_to_change_to);
						Containers::worldObj_table[collide_with]->setHeight(value_to_change_to);
					}
					else if (variable_for_change == "xloc")
					{
						std::cout << "////////////////////////" << endl;
						std::cout << "ENTER X LOC AS FLOAT: ";

						float value_to_change_to;
						cin >> value_to_change_to;

						Containers::worldObj_table[collide_with]->setX(value_to_change_to);
					}
					else if (variable_for_change == "yloc")
					{
						std::cout << "////////////////////////" << endl;
						std::cout << "ENTER Y LOC AS FLOAT: ";

						float value_to_change_to;
						cin >> value_to_change_to;

						Containers::worldObj_table[collide_with]->setY(value_to_change_to);

					}
					else if (variable_for_change == "offset")
					{
						std::cout << "////////////////////////" << endl;
						std::cout << "ENTER BODY NUMBER AS INT(0 if only one body): ";
						cin >> body_number;

						std::cout << "ENTER LEFT LOC AS FLOAT: ";
						cin >> left;

						std::cout << "ENTER RIGHT LOC AS FLOAT: ";
						cin >> right;

						std::cout << "ENTER TOP LOC AS FLOAT: ";
						cin >> top;

						std::cout << "ENTER BOTTOM LOC AS FLOAT: ";
						cin >> bottom;

						Containers::worldObj_table[collide_with]->offsetBody(body_number, left, right, top, bottom);
				
						std::cout << "///////////////////////////////////" << endl;
						std::cout << "body X is " << Containers::worldObj_table[collide_with]->body[body_number].getX() << " and Y is " << Containers::worldObj_table[collide_with]->body[body_number].getY() << endl;
						std::cout << "body X is " << Containers::worldObj_table[collide_with]->body[body_number].getX() << " and Y is " << Containers::worldObj_table[collide_with]->body[body_number].getY() << endl;
						std::cout << "///////////////////////////////////" << endl;

					}
				}
				//this adds the object to the config file
				Json::Value root;
				Json::Reader reader;

				std::ifstream in_file("config.json");
				in_file >> root;
				in_file.close();

				std::ofstream file;
				file.open("config.json");


				//populate 'value_obj' with the objects, arrays etc.
				Json::Value new_obj = {};

				new_obj["x"] = Containers::worldObj_table[collide_with]->getX() / 100;
				new_obj["y"] = Containers::worldObj_table[collide_with]->getY() / 100;
				new_obj["hight"] = Containers::worldObj_table[collide_with]->getHeight();
				new_obj["width"] = Containers::worldObj_table[collide_with]->getWidth();
				new_obj["frame_num"] = Containers::worldObj_table[collide_with]->body.size();
				new_obj["name"] = collide_with;
				string tex_file = Containers::worldObj_table[collide_with]->sprite.getTexture().getFile();
				tex_file = tex_file.substr(15, tex_file.size()); //shaves off front
				tex_file = tex_file.substr(0, tex_file.size() - 4); //shaves off tail
				new_obj["tex_file"] = tex_file;

				new_obj["bodyx1"] = (Containers::worldObj_table[collide_with]->offset_x1);
				
				new_obj["bodyx2"] = (Containers::worldObj_table[collide_with]->offset_x2);

				new_obj["bodyy1"] = (Containers::worldObj_table[collide_with]->offset_y1);

				new_obj["bodyy2"] = (Containers::worldObj_table[collide_with]->offset_y2);
									

				root[collide_with] = new_obj;

				Json::StyledWriter styledWriter;
				file << styledWriter.write(root);

				file.close();



			}
		}
		
	}

	if (DialogueController::getState() > 0) {
		if (Q) {
			//DialogueController::exitDialogue();

			WorldObj* other = DialogueController::getOther();
			std::cout << "HERO: " << other->getName() << std::endl;
			if (other->getType() == 5) {
				std::cout << "Right type" << std::endl;
				Hero* them = dynamic_cast<Hero*>(other);
				Planner* planner = ai->hero_planners[them->name];
				//DialogueController::prompted_quest = true;
				if (planner->give_as_quest && !DialogueController::accepted_quest)
				{
					DialogueController::quest = planner->get_current_action();
                    DialogueController::offerQuest_hack_();
					DialogueController::prompted_quest = true;
				}
				else
				{
					DialogueController::exitDialogue();
				}
			}
			else
			{
				DialogueController::exitDialogue();
			}
		}
		if (DialogueController::prompted_quest) {
			
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
		if (count == 10) {
			disable = false;
			count = 0;
		}
		if (!disable) {
			int State = DialogueController::getState();
			if (W && State == 1) {
				int tmp = DialogueController::getOptionsIndex();
				if (tmp > 0) {
					DialogueController::setOptionsIndex(--tmp);
					disable = true;
					////std::cout << "OptionsIndex: " << tmp << std::endl;
					switch (DialogueController::getOptionsIndex()) {
					case 0: gameplay_functions->setSwordGlow(player); break;
					case 1: gameplay_functions->setHeartGlow(player); break;
					case 2: gameplay_functions->setFaceGlow(player); break;
					case 3: gameplay_functions->setQuestionGlow(player); break;
					}
				}
			}
			if (S && State == 1) {
				int tmp = DialogueController::getOptionsIndex();
				if (tmp < DialogueController::getOSize() - 1) {
					DialogueController::setOptionsIndex(++tmp);
					disable = true;
					////std::cout << "OptionsIndex: " << tmp << std::endl;
					switch (DialogueController::getOptionsIndex()) {
					case 0: gameplay_functions->setSwordGlow(player); break;
					case 1: gameplay_functions->setHeartGlow(player); break;
					case 2: gameplay_functions->setFaceGlow(player); break;
					case 3: gameplay_functions->setQuestionGlow(player); break;
					}
				}
			}
			if (D && State < 3) {
				int tmp = DialogueController::getSelect();
				if (DialogueController::getState() == 1) {
					if (tmp < (DialogueController::getOptions().size() - 1)) {
						DialogueController::setSelect(++tmp);
						disable = true;
						////std::cout << "Index: " << tmp << std::endl;
					}
					if (tmp > (DialogueController::getOptions().size() - 1)) {
						tmp = 0;
						DialogueController::setSelect(tmp);
						disable = true;
						////std::cout << "Index: " << tmp << std::endl;
					}
				}
				if (State == 2) {
					if (tmp < (DialogueController::getReplyOptions().size() - 1)) {
						DialogueController::setSelect(++tmp);
						disable = true;
						////std::cout << "Index: " << tmp << std::endl;
					}
					if (tmp > (DialogueController::getReplyOptions().size() - 1)) {
						tmp = 0;
						DialogueController::setSelect(tmp);
						disable = true;
						////std::cout << "Index: " << tmp << std::endl;
					}
				}
			}
			if (A && State < 3) {
				int tmp = DialogueController::getSelect();
				if (tmp > 0) {
					DialogueController::setSelect(--tmp);
					disable = true;
					////std::cout << "Index: " << tmp << std::endl;
				}
			}
			if (ENTER) {
				////std::cout << "ENTER" << std::endl;
				if (DialogueController::getState() == 1) {
					disable = true;
					DialogueController::PlayerConversationPoint();
				}
				else if (DialogueController::getState() == 2) {
					disable = true;
					DialogueController::PlayerResponse();
				//	DialogueController::prompted_quest = false;
				}
			}
		}
		else {
			count++;
		}
	}
}





