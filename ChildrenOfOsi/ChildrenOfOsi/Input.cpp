#include "stdafx.h"
#include "Input.h"
#include <conio.h>
#include <Windows.h>
#include "Soldier.h"
#include "Attack.h"
#include "CheckClass.h"
#include "json.h"
#include "RegionState.h"


Input::Input(ChildrenOfOsi* _gameplay_functions, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec, vector<WorldObj*>* _movVec)
{
	count = 0;
	count2 = 0;
	gameplay_functions = _gameplay_functions;
	rHelper = _rHelper;
	tBuffer = _tBuffer;
	recVec = _recVec;
	movVec = _movVec;
	current_game_state = game_state::load_game;
	LOG("Input Objected Constructed");
}

Input::Input(ChildrenOfOsi* _gameplay_functions, WorldObj * _player, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec, vector<WorldObj*>* _movVec)
{
	count = 0;
	count2 = 0;
	gameplay_functions = _gameplay_functions;
	rHelper = _rHelper;
	tBuffer = _tBuffer;
	recVec = _recVec;
	movVec = _movVec;
	//gameplay_functions->play_sound("Play");
	//gameplay_functions->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav");
	//gameplay_functions->play_sound("Walk");
	//gameplay_functions->pause_unpause("Pause", "walk_loop.wav");
	//gameplay_functions->play_sound("Pause");
	//gameplay_functions->play_sound("Sixers");
	player = _player;
	current_game_state = game_state::load_game;
	LOG("Input Object W/Player Constructed");
}


Input::~Input()
{
	LOG("Input Objected Destroyed");
}

//map editor functions

///adds a new object to the game
void Input::add_object() {

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
		//////cout << image_name << "Already in Table /////////////////////////////" << endl;
	}
	else
	{
		//////cout << image_name << "Not in Table /////////////////////////////" << endl;
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

void Input::edit_field(std::string collide_with, int body_number, float left, float right, float top, float bottom) {

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


void Input::duplicate_object(std::string collide_with) {
	//this adds the object to the config file
	Json::Value root;
	Json::Reader reader;

	std::ifstream in_file("config.json");
	in_file >> root;
	in_file.close();

	std::ofstream file;
	file.open("config.json");

	int dup_num;
	int row_size;
	int if_rand;

	std::cout << "////////////////////////" << endl;
	std::cout << "HOW MANY DUPLICATES WOULD YOU LIKE TO MAKE: ";
	cin >> dup_num;

	std::cout << "////////////////////////" << endl;
	std::cout << "HOW MANY OBJ PER ROW: ";
	cin >> row_size;

	std::cout << "////////////////////////" << endl;
	std::cout << "WOULD YOU LIKE TO RANDOMIZE(not working right now): ";
	cin >> if_rand;

	int row_count = 1;
	int column_count = 1;

	for (int i = 0; i < dup_num; i++)
	{

		//populate 'value_obj' with the objects, arrays etc.
		Json::Value new_obj = {};

		std::string obj_name = collide_with + "-" + std::to_string(i);
		//
		new_obj["x"] = (Containers::worldObj_table[collide_with]->getX() / 100) +
			row_count*(Containers::worldObj_table[collide_with]->getWidth() / 100 + 1) + 5; //this is so it spaces it by the width
		new_obj["y"] = (Containers::worldObj_table[collide_with]->getY() / 100) +
			column_count*(Containers::worldObj_table[collide_with]->getHeight() / 100 + 1); //this is so it spaces it by the width;
		new_obj["hight"] = Containers::worldObj_table[collide_with]->getHeight();
		new_obj["width"] = Containers::worldObj_table[collide_with]->getWidth();
		new_obj["frame_num"] = Containers::worldObj_table[collide_with]->body.size();
		new_obj["name"] = obj_name;
		string tex_file = Containers::worldObj_table[collide_with]->sprite.getTexture().getFile();
		tex_file = tex_file.substr(15, tex_file.size()); //shaves off front
		tex_file = tex_file.substr(0, tex_file.size() - 4); //shaves off tail
		new_obj["tex_file"] = tex_file;

		new_obj["bodyx1"] = (Containers::worldObj_table[collide_with]->offset_x1);

		new_obj["bodyx2"] = (Containers::worldObj_table[collide_with]->offset_x2);

		new_obj["bodyy1"] = (Containers::worldObj_table[collide_with]->offset_y1);

		new_obj["bodyy2"] = (Containers::worldObj_table[collide_with]->offset_y2);

		root[obj_name] = new_obj;

		gameplay_functions->add_worldObj(obj_name, new_obj["x"].asFloat(), new_obj["y"].asFloat(), true);

		tBuffer->run();

		Containers::worldObj_table[obj_name]->sprite.setTexture(Containers::texture_table[tex_file]);
		Containers::worldObj_table[obj_name]->setInteractable(false);


		Containers::worldObj_table[obj_name]->setX(new_obj["x"].asFloat() * 100);
		Containers::worldObj_table[obj_name]->setY(new_obj["y"].asFloat() * 100);
		Containers::worldObj_table[obj_name]->setHeight(new_obj["hight"].asFloat());
		Containers::worldObj_table[obj_name]->setWidth(new_obj["width"].asFloat());
		//Containers::worldObj_table[obj_name]->frame number
		Containers::worldObj_table[obj_name]->setName(obj_name);
		Containers::worldObj_table[obj_name]->offsetBody(0, new_obj["bodyx1"].asFloat(),
			new_obj["bodyx2"].asFloat(),
			new_obj["bodyy1"].asFloat(),
			new_obj["bodyy2"].asFloat());

		recVec->push_back(Containers::worldObj_table[obj_name]);
		//cout << obj_name << endl;
		//cout << Containers::worldObj_table[obj_name]->getHeight() << endl;
		//cout << "the newobj: " << new_obj["hight"] << endl;
		//cout << "the x: " << Containers::worldObj_table[obj_name]->getX() << endl;

		if (row_count == row_size) {
			row_count = 1;
			column_count++;
		}
		else
		{
			row_count++;
		}



	}

	Json::StyledWriter styledWriter;
	file << styledWriter.write(root);

	file.close();
}


void Input::delete_object(std::string collide_with)
{
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


	root[collide_with] = new_obj;

	Json::StyledWriter styledWriter;
	file << styledWriter.write(root);

	file.close();

	Containers::worldObj_table[collide_with]->setX(0);
	Containers::worldObj_table[collide_with]->setY(0);

}

void Input::interactive_resize(std::string collide_with, double mouseX)
{
	if (previous_x_mouse_pos != mouseX)
	{
		double value_to_change_to = mouseX - previous_x_mouse_pos;
		//cout << value_to_change_to << endl;
		if (std::abs(value_to_change_to) < 200)
		{
			Containers::worldObj_table[collide_with]->setWidth
			(Containers::worldObj_table[collide_with]->getWidth() + value_to_change_to);
			Containers::worldObj_table[collide_with]->setHeight
			(Containers::worldObj_table[collide_with]->getHeight() + value_to_change_to);
		}

		previous_x_mouse_pos = mouseX;
	}
}




///edit an existing object
void Input::edit_object() {

	short L = GetKeyState('L') >> 15;
	short K = GetKeyState('K') >> 15;
	short J = GetKeyState('J') >> 15;
	short H = GetKeyState('H') >> 15;

	short O = GetKeyState('O') >> 15;
	short I = GetKeyState('I') >> 15;
	short P = GetKeyState('P') >> 15;

	/*POINT p;
	if (ScreenToClient(window, &p))
	{
	//////cout << "////////////////////////" << endl;
	//////cout << p.x << p.y << endl;
	//////cout << "////////////////////////" << endl;
	}*/

	double xpos;
	double ypos;
	glfwGetCursorPos(GameWindow::window, &xpos, &ypos);

	bool onscreen = true;
	//checks if the mouse is off screen
	if (xpos < 0 || xpos > 1300 ||
		ypos < 0 || ypos > 700)
	{
		onscreen = false;
		std::cout << "onscreen: " << onscreen << endl;
	}

	//this map_zoom is used to zoom out the game for map editor mode
	int zoom = 4;

	double mouseX = rHelper->camera->getX() + (xpos * map_zoom) * GameWindow::WINDOW_WIDTH_DP / 1300;
	double mouseY = rHelper->camera->getY() + (ypos * map_zoom) * GameWindow::WINDOW_HEIGHT_DP / 700;


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

		}
	}

	if (collide_with != "" && onscreen && collide_with != "JungleVillage" && collide_with != "Oasis_Platform")
	{
		if (!H)
		{
			Containers::worldObj_table[collide_with]->setX(mouseX - (Containers::worldObj_table[collide_with]->getWidth()) / 2);
			Containers::worldObj_table[collide_with]->setY(mouseY - (Containers::worldObj_table[collide_with]->getHeight()) / 2);

			previous_x_mouse_pos = 0;
		}
		string tex_file = Containers::worldObj_table[collide_with]->sprite.getTexture().getFile();
		tex_file = tex_file.substr(15, tex_file.size()); //shaves off front
		tex_file = tex_file.substr(0, tex_file.size() - 4); //shaves off tail

		//prints out current info for what is being clicked 
		std::cout << "HIGHT: " << Containers::worldObj_table[collide_with]->getHeight() << endl;
		std::cout << "WIDTH: " << Containers::worldObj_table[collide_with]->getWidth() << endl;
		std::cout << "X LOC: " << Containers::worldObj_table[collide_with]->getX() << endl;
		std::cout << "Y LOC: " << Containers::worldObj_table[collide_with]->getY() << endl;

		std::cout << "BODY x1: " << Containers::worldObj_table[collide_with]->offset_x1 << endl;
		std::cout << "BODY x2: " << Containers::worldObj_table[collide_with]->offset_x2 << endl;
		std::cout << "BODY y1: " << Containers::worldObj_table[collide_with]->offset_y1 << endl;
		std::cout << "BODY y2: " << Containers::worldObj_table[collide_with]->offset_y2 << endl;


		std::cout << "TEXTURE: " << tex_file << endl;


		int body_number = 0;
		float left = 0.0;
		float right = 0.0;
		float top = 0.0;
		float bottom = 0.0;

		if (L)
		{
			edit_field(collide_with, body_number, left, right, top, bottom);
		}
		else if (I)
		{
			duplicate_object(collide_with);
		}
		else if (O)
		{
			interactive_resize(collide_with, mouseX);
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
		new_obj["tex_file"] = tex_file;

		new_obj["bodyx1"] = (Containers::worldObj_table[collide_with]->offset_x1);

		new_obj["bodyx2"] = (Containers::worldObj_table[collide_with]->offset_x2);

		new_obj["bodyy1"] = (Containers::worldObj_table[collide_with]->offset_y1);

		new_obj["bodyy2"] = (Containers::worldObj_table[collide_with]->offset_y2);


		root[collide_with] = new_obj;

		Json::StyledWriter styledWriter;
		file << styledWriter.write(root);

		file.close();

		if (P)
		{
			delete_object(collide_with);
		}
	}
}


void Input::add_point_to_file(std::string file_name) {
	double xpos;
	double ypos;
	glfwGetCursorPos(GameWindow::window, &xpos, &ypos);
	////cout << "XPOS AND YPOS ARE " << xpos << ", " << ypos << endl;

	int mouseX = (rHelper->camera->getX() + (xpos * map_zoom) * GameWindow::WINDOW_WIDTH_DP / 1280);
	int mouseY = 25000 - (rHelper->camera->getY() + (ypos * map_zoom) * GameWindow::WINDOW_HEIGHT_DP / 720);
	//int mouseX = rHelper->camera->getX() - (150.0 / 2) + ((rHelper->getCameraSize().getXloc() / 2)*map_zoom);
	//int mouseY = rHelper->camera->getY() - (150.0 / 2) + ((rHelper->getCameraSize().getYloc() / 2)*map_zoom);

	std::ofstream rivFile;
	rivFile.open(file_name, std::ios_base::app);
	rivFile << mouseX << " " << mouseY << " ";
	rivFile.close();
	rivFile.clear();
	oldPoint.first = mouseX; oldPoint.second = mouseY;

	rHelper->rivObj->initialize_lines();
	system("PAUSE");
}

void Input::skip_line(std::string file_name) {
	std::ofstream rivFile;
	rivFile.open(file_name, std::ios_base::app);
	rivFile << endl;
	rivFile << oldPoint.first << " " << oldPoint.second << " ";
	rivFile.close();
	rivFile.clear();
	system("PAUSE");
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
	short H = GetKeyState('H') >> 15; //set home point
	short I = GetKeyState('I') >> 15;
	short J = GetKeyState('J') >> 15; // Base attack
	short K = GetKeyState('K') >> 15; // Projectile
	short L = GetKeyState('L') >> 15; // Spin attack
	short SEMI = GetKeyState(';') >> 15; // Fire
	short ENTER = GetKeyState(VK_RETURN) >> 15;
	short SHIFT = GetKeyState(VK_LSHIFT) >> 15;
	short ESC = GetKeyState(VK_ESCAPE) >> 15;
	short V = GetKeyState('V') >> 15; //set patrol point
	short F = GetKeyState('F') >> 15;
	short P = GetKeyState('P') >> 15;
	short Z = GetKeyState('Z') >> 15;
	short G = GetKeyState('G') >> 15; //Put party in defense mode
	short Y = GetKeyState('Y') >> 15; //Put party in attack mode
	short U = GetKeyState('U') >> 15; //Puts party in flee mode
	short M = GetKeyState('M') >> 15;

	short ONE = GetKeyState('1') >> 15;  //clear patrol points
	short TWO = GetKeyState('2') >> 15; //Removes you from party and puts party in flee mode
	short THREE = GetKeyState('3') >> 15; // Remove self from party and put party in patrol mode
	short FOUR = GetKeyState('4') >> 15; // coming soon

	// main menu, only allow W and S to select menu options
	if (current_game_state == game_state::main_menu) {
		if (W) {
			// move selected option up
		}
		if (S) {
			// move selected option down
		}
		if (ENTER) {
			// assuming menu only has start option, so move in game
			if (current_game_state == game_state::main_menu) {
				current_game_state = game_state::in_game;
			}
		}
	}
	if (current_game_state == game_state::in_game) {
		if (DialogueController::getState() == 0) {

			Player* t = CheckClass::isPlayer(player);
			gameplay_functions->combat(player);
			if (SHIFT) {
				if (t->getStamina() > 0) {
					t->setSpeed(10);
					t->setStamina(t->getStamina()-1);
				}
				if (MAP_EDITOR) { t->setSpeed(15 * 2); }
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
				//////std:://cout << "Pressed E" << std::endl;
				gameplay_functions->talk(player);
			}
			if (MAP_EDITOR == 0)
			{
				if ((W || A || S || D) && J) {
					if (t->getCool()) {
						//////std:://cout << "Pressed Moving J" << std::endl;
						t->flipSwing();
						t->meleeAttack();
						gameplay_functions->melee(t);
					}
				}
				else if (J) {
					if (t) {
						if (t->getCool()) {
							//////std:://cout << "Pressed F" << std::endl;
							t->meleeAttack();
							gameplay_functions->melee(t);
						}
						else if (t->getCombo()) {
							//////std:://cout << "COMBO" << std::endl;
							t->sprite.unlockAnimation();
							t->resetCD();
							if (t->getCool()) {
								//////std:://cout << "Pressed F" << std::endl;
								t->flipSwing();
								t->meleeAttack();
								gameplay_functions->melee(t);
							}
							else {
								t->sprite.lockAnimation();
							}
						}
					}
				}
				else if (K) {
					if (t) {
						if (t->getCool(1)) {
							//////std:://cout << "Pressed Shift+R" << std::endl;
							gameplay_functions->special(t, 1);
							gameplay_functions->fire(t);
						}
					}
				}
				/*else if (K) {
					if (t) {
						if (t->getCool(0)) {
							//////std:://cout << "Pressed R" << std::endl;
							gameplay_functions->special(t, 0);
							gameplay_functions->melee(t);
						}
					}
				}*/
				else if (L) {
					if (t) {
						if (t->getCool(2)) {
							//////std:://cout << "Pressed T" << std::endl;
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
				if (Y) {
					t->getParty()->set_defend(t->getLoc());
					t->getParty()->setMode(Party::MODE_DEFEND);
					t->getParty()->removeSoldier(t, true);
				}
				if (I) {
					t->getParty()->setMode(Party::MODE_ATTACK);
				}
				if (U) {
					t->getParty()->setMode(Party::MODE_FLEE);
				}
			/*	if (H) {
					t->getParty()->set_home(t->getLoc());
				}*/
				if (ONE) {
					t->getParty()->clear_patrol_route();
				}
				if (count2 > 0)count2--;
				if (V && (count2 == 0)) {
					t->getParty()->add_patrol_loc(t->getLoc());
					count2 = 200;
				}
				if (TWO && (count2 == 0)) {
					t->getParty()->setMode(Party::MODE_FLEE);
					t->getParty()->removeSoldier(t, true);
					t->getVillage()->addToParties(t->getParty());
					count2 = 200;
				}
				if (THREE && (count2 == 0)) {
					t->getParty()->setMode(Party::MODE_PATROL);
					t->getParty()->removeSoldier(t, true);
					t->getVillage()->addToParties(t->getParty());
					count2 = 200;
				}
				if (M && (count2 == 0)) {
					HUD::toggle_quests();
					count2 = 20;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
					double xpos;
					double ypos;
					glfwGetCursorPos(GameWindow::window, &xpos, &ypos);
					double mouseX = rHelper->camera->getX() + (xpos * map_zoom) * GameWindow::WINDOW_WIDTH_DP / 1280;
					double mouseY = 25000 - (rHelper->camera->getY() + (ypos * map_zoom) * GameWindow::WINDOW_HEIGHT_DP / 720);
					//for (int i = 0; i < 10; i++) {
						cout << "MOUSEX AND MOUSEY ARE " << mouseX << ", " << mouseY << endl;

						cout << "XPOS AND YPOS ARE " << xpos << ", " << ypos << endl;
					//}

				}

				/**********      river collision line config       *********/
				if (P && (GetKeyState(VK_LBUTTON) & 0x100) != 0) {
					add_point_to_file("rivLine.txt");
				}
			
				if (Z) {
					skip_line("rivLine.txt");
				}

				/*******************/

				/**********      oasis collision line config       *********/ 
				//if holding numpad 9 and left mouse
				if ((GetKeyState(VK_NUMPAD9) & 0x100) != 0 && (GetKeyState(VK_LBUTTON) & 0x100) != 0) {
					add_point_to_file("oasis.txt");
				}
				if ((GetKeyState(VK_NUMPAD8) & 0x100) != 0) {
					skip_line("oasis.txt");
				}

				/*******************/

				if (ESC) {
					if (current_game_state == game_state::in_game) {
						cout << "running escape input" << endl;
						current_game_state = game_state::pause_menu;
						return;
					}
				}


				//where the map editor is executed
				////////////////////////////////////
			}
			else if (MAP_EDITOR == 1) {
				if (L && (GetKeyState(VK_LBUTTON) & 0x100) == 0)
				{
					add_object();
				}

				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
				{
					edit_object();
				}
			}
			////////////////////////////////////

		}
		if (DialogueController::getState() > 0) {
			if (count > 0) {
				count--;
			}
			/*if (SHIFT && Q && count == 0) {
				WorldObj* other = DialogueController::getOther();
				if (other->getType() > WorldObj::TYPE_NPC) {
					Soldier* follower = dynamic_cast<Soldier*>(other);
					Player* t = dynamic_cast<Player*>(player);
					//cout << t->getParty()->getAlliance() << " = " << follower->getParty()->getAlliance() << endl;
					if (t->getParty() == follower->getParty()) {
						t->getParty()->removeSoldier(follower, true);
						follower->getVillage()->addToParties(follower->getParty());
					}
					else if (t->getParty()->getAlliance() == follower->getParty()->getAlliance()) {
						if (follower->getParty()->getMembers().size() <= 1)follower->getVillage()->remove_party(follower->getParty());
						follower->getParty()->removeSoldier(follower, false);
						t->getParty()->addToParty(follower, false);
					}
				}
				count = 10;
			}*/
			if (Q) {
				//DialogueController::exitDialogue();
				//DialogueController::state = 7;
				DialogueController::create_farewell();

				/*WorldObj* other = DialogueController::getOther();
				//std:://cout << "HERO: " << other->getName() << std::endl;
				if (other->getType() == WorldObj::TYPE_HERO) {
					std::cout << "Right type" << std::endl;
					Hero* them = dynamic_cast<Hero*>(other);
					Planner* planner = AIController::get_plan(them->name);
					//DialogueController::prompted_quest = true;
					if (player == AIController::pick_quest_doer(planner->get_current_action()))
					{
						std::cout << "Post convo, " << them->getName() << "now wants to give Shango their '" << planner->get_current_action() << "' action" << std::endl;
					}
					else
					{
						std::cout << "Post convo, " << them->getName() << "still does not want to give Shango their '" << planner->get_current_action() << "' action" << std::endl;
					}
					if (planner->give_as_quest && !DialogueController::accepted_quest)
					{
						//DialogueController::quest = planner->get_current_action();
						//DialogueController::offerQuest_hack_();
						//DialogueController::prompted_quest = true;
					}
					else
					{
						gameplay_functions->change_song("Change", RegionState::current_region.getRTheme(), RegionState::current_region.getRTheme());
						RegionState::in_village = false;
						DialogueController::exitDialogue();
					}*/
				//}
				//else
				//{
					gameplay_functions->change_song("Change", RegionState::current_region.getRTheme(), RegionState::current_region.getRTheme());
					RegionState::in_village = false;
					DialogueController::exitDialogue();
				//}
			}
			if (T) {
				Hero* them = dynamic_cast<Hero*>(DialogueController::getOther());
				if (them) {
					Player* me = dynamic_cast<Player*>(player);
					me->remove_quest(AIController::get_plan(them->name)->get_current_action());
				}
			}
			if (J) {
				DialogueController::setOptionsIndex(0);
				gameplay_functions->setSwordGlow(player);
			}
			if (K) {
				DialogueController::setOptionsIndex(1);
				gameplay_functions->setHeartGlow(player);
			}
			if (L) {
				DialogueController::setOptionsIndex(2);
				gameplay_functions->setFaceGlow(player);
			}
			if (SEMI) {
				DialogueController::setOptionsIndex(3);
				gameplay_functions->setQuestionGlow(player);
			}
			if (count == 0) {
				int State = DialogueController::getState();
				if (A && State == 1) {
					DialogueController::scroll_control = 0;
					int tmp = DialogueController::getOptionsIndex();
					if (tmp > 0) {
						DialogueController::setOptionsIndex(--tmp);
						count = 10;
						gameplay_functions->createTaskForAudio("PlaySound","SOUND", "SFX/page.wav");
						//////std:://cout << "OptionsIndex: " << tmp << std::endl;
						switch (DialogueController::getOptionsIndex()) {
						case 0: gameplay_functions->setSwordGlow(player); break;
						case 1: gameplay_functions->setHeartGlow(player); break;
						case 2: gameplay_functions->setFaceGlow(player); break;
						case 3: gameplay_functions->setQuestionGlow(player); break;
						}
					}

				}
				if (D && State == 1) {
					DialogueController::scroll_control = 0;
					Hero* temp_hero = CheckClass::isHero(DialogueController::getOther());
					int tmp = DialogueController::getOptionsIndex();
					if (temp_hero) {
						//int tmp = DialogueController::getOptionsIndex();
						if (tmp < DialogueController::getOSize() - 1) {
							
							DialogueController::setOptionsIndex(++tmp);
							count = 10;
							if (tmp <= DialogueController::getOSize() - 1)
								gameplay_functions->createTaskForAudio("PlaySound", "SOUND", "SFX/page.wav");
							//////std:://cout << "OptionsIndex: " << tmp << std::endl;
							switch (DialogueController::getOptionsIndex()) {
							case 0: gameplay_functions->setSwordGlow(player); break;
							case 1: gameplay_functions->setHeartGlow(player); break;
							case 2: gameplay_functions->setFaceGlow(player); break;
							case 3: gameplay_functions->setQuestionGlow(player); break;
							}

						}
					}
					else {
						if (tmp < DialogueController::getOSize() - 1) {
							DialogueController::setOptionsIndex(++tmp);
							count = 10;
							//////std:://cout << "OptionsIndex: " << tmp << std::endl;
							switch (DialogueController::getOptionsIndex()) {
							case 0: gameplay_functions->setSwordGlow(player); break;
							case 1: gameplay_functions->setHeartGlow(player); break;
							case 2: gameplay_functions->setFaceGlow(player); break;
							case 3: gameplay_functions->setQuestionGlow(player); break;
							}

						}

					}
					/*set optionsIndex to 3 if player hits 's' key while they are already
					on the question mark icon because in this case optionsIndex would
					become greater than 3 and there are only options to
					display at indices 0,1,2,3*/
					if (tmp > 3) {
						DialogueController::setOptionsIndex(3);
						gameplay_functions->setQuestionGlow(player);
					}

				}
				if (S && State < 3) {
					int tmp = DialogueController::getSelect();
					Hero* temp_hero = CheckClass::isHero(DialogueController::getOther());
					if (DialogueController::getState() == 1 && temp_hero) {
						if (tmp < (DialogueController::getOptions().size() - 1)) {
							//DialogueController::setSelect(++tmp);
							DialogueController::scroll_control++;
							if (DialogueController::scroll_control >= DialogueController::getOptions().size()) 
								DialogueController::scroll_control = DialogueController::getOptions().size() - 1;
							else
								gameplay_functions->createTaskForAudio("PlaySound", "SOUND", "SFX/down.wav");
						

							count = 10;
							//////std:://cout << "Index: " << tmp << std::endl;
						}
						if (tmp >(DialogueController::getOptions().size() - 1)) {
							tmp = 0;
							DialogueController::setSelect(tmp);
							//DialogueController::scroll_control++;
							if (DialogueController::scroll_control < 0)
								DialogueController::scroll_control = 0;
							count = 10;
							//////std:://cout << "Index: " << tmp << std::endl;
						}
					}
					else if (DialogueController::getState() == 1) {
						if (tmp < (DialogueController::get_soldier_options().size() - 1)) {
							//DialogueController::setSelect(++tmp);
							DialogueController::scroll_control++;
							if (DialogueController::scroll_control >= DialogueController::get_soldier_options().size()) {
								DialogueController::scroll_control = DialogueController::get_soldier_options().size() - 1;
								gameplay_functions->createTaskForAudio("PlaySound", "SOUND", "SFX/down.wav");
							}
							count = 10;
							//////std:://cout << "Index: " << tmp << std::endl;
						}
						if (tmp >(DialogueController::get_soldier_options().size() - 1)) {
							tmp = 0;
							DialogueController::setSelect(tmp);
							//DialogueController::scroll_control++;
							if (DialogueController::scroll_control < 0)
								DialogueController::scroll_control = 0;
							count = 10;
							//////std:://cout << "Index: " << tmp << std::endl;
						}
					}
					if (State == 2) {
						if (tmp < (DialogueController::getReplyOptions().size() - 1)) {
							//DialogueController::setSelect(++tmp);
							DialogueController::scroll_control++;
							if (DialogueController::scroll_control >= DialogueController::getReplyOptions().size()) 
							DialogueController::scroll_control = DialogueController::getReplyOptions().size() - 1;
							else
								gameplay_functions->createTaskForAudio("PlaySound", "SOUND", "SFX/down.wav");
						
							

							count = 10;
							//////std:://cout << "Index: " << tmp << std::endl;
						}
						if (tmp >(DialogueController::getReplyOptions().size() - 1)) {
							tmp = 0;
							DialogueController::setSelect(tmp);
							//DialogueController::scroll_control++;
							if (DialogueController::scroll_control < 0)
								DialogueController::scroll_control = 0;
							count = 10;
							//////std:://cout << "Index: " << tmp << std::endl;
						}
					}
				}
				if (W && State < 3) {
					int tmp = DialogueController::getSelect();
					if (tmp > 0 || DialogueController::scroll_control > 0) {
						//DialogueController::setSelect(--tmp);
						
						DialogueController::scroll_control--;
						if (DialogueController::scroll_control < 0)
							DialogueController::scroll_control = 0;
						else
							gameplay_functions->createTaskForAudio("PlaySound", "SOUND", "SFX/up.wav");
						//disable = true;
						count = 10;
						//////std:://cout << "Index: " << tmp << std::endl;
					}
				}
				if (ENTER) {
					//////std:://cout << "ENTER" << std::endl;
					if (DialogueController::getState() == 1) {
						count = 10;
						Hero* temp_hero;
						if (temp_hero = CheckClass::isHero(DialogueController::getOther()))
                            DialogueController::PlayerConversationPoint();
						else if (DialogueController::optionsIndex == 0)
							DialogueController::player_conversation_point_soldier();
					}
					else if (DialogueController::getState() == 2) {
						count = 10;
						DialogueController::PlayerResponse();
						//	DialogueController::prompted_quest = false;
					}
					else if (DialogueController::getState() == 5) {
						count = 10;
						Hero* temp_hero;
						if(temp_hero = CheckClass::isHero(DialogueController::getOther()))
						    DialogueController::PlayerConversationPoint();
						else
							DialogueController::player_conversation_point_soldier();
					}
					else if (DialogueController::getState() == 6) {
						count = 10;
						DialogueController::PlayerResponse();
					}
					else if (DialogueController::getState() == 7) {
						count = 10;
						gameplay_functions->change_song("Change", RegionState::current_region.getRTheme(), RegionState::current_region.getRTheme());
						RegionState::in_village = false;
						DialogueController::exitDialogue();
					}
					else if (DialogueController::getState() == 8) {
						count = 10;
						DialogueController::otherResponse("","");
					}
					else if (DialogueController::getState() == 9) {
						count = 10;
						gameplay_functions->change_song("Change", RegionState::current_region.getRTheme(), RegionState::current_region.getRTheme());
						RegionState::in_village = false;
						DialogueController::exitDialogue();
						if (dynamic_cast<Player*>(Containers::hero_table["Shango"])->cur_action != nullptr) 
						{
							PlayerActExecFunctions::execute_dialog();
						}
						
					}
					else if (DialogueController::getState() == 10) {
						count = 10;
						DialogueController::create_farewell();
						DialogueController::state = 7;
					}
				}
			}
		}
	}
	if (current_game_state == game_state::pause_menu) {
		// pressing esc to unpause
		//cout << "IN PUT CONTROL IS IN PAUSE STATE" << endl;
		if (ENTER) {
			//for (int i = 0; i < 10; i++) cout << "I HAVE JUST PRESSED Q" << endl;
			if (current_game_state == game_state::pause_menu) {
				current_game_state = game_state::in_game;
			}
		}
	}
}





