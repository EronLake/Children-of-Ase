#pragma once
#include "stdafx.h"
#include "common.h"
#include "ChildrenOfOsi.h"
#include "DialogueController.h"
#include "GameWindow.h"
#include "RenderHelper.h"
#include "Containers.h"
#include "AIController.h"
#include "Village.h"
#include "GameState.h"



class Input
{
private:
	WorldObj* player;
	ChildrenOfOsi* gameplay_functions;
	RenderHelper* rHelper;
	TaskBuffer* tBuffer;
	vector<WorldObj*>* recVec;
	vector<WorldObj*>* movVec;
	AIController* ai;
	pair<float, float> oldPoint;

	short W;
	short A;
	short S;
	short D;
	short Q;
	short E;
	short F;
	int count;
	int count2;

  bool locked = false;
	bool prompted_quest = false;

	bool coordOverlap(int value, int min, int max) { return (value >= min) && (value <= max); }

	//Map Editor Functions  
	void add_object();
	void edit_object();
	void edit_field(std::string collide_with, int body_number, float left, float right, float top, float bottom);
	void duplicate_object(std::string collide_with);
	void delete_object(std::string collide_with);
	double previous_x_mouse_pos = 0;
	void interactive_resize(std::string collide_with, double mouseX);

	//River/Mountain Point Tool
	void add_point_to_file(std::string file_name);
	void skip_line(std::string file_name);

public:
	Input(ChildrenOfOsi* _gameplay_functions, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec, vector<WorldObj*>* _movVec);
	Input(ChildrenOfOsi* _gameplay_functions, WorldObj * _player, RenderHelper* _rHelper, TaskBuffer* _tBuffer, vector<WorldObj*>* _recVec, vector<WorldObj*>* _movVec);
	~Input();
	//Region* Desert;
	//Region* Ogun;
	//Region* Mountain;
	//Region* Jungle;
	//Region current_region;
	//Region next_region;

	void InputCheck();
	game_state current_game_state;
	

};

