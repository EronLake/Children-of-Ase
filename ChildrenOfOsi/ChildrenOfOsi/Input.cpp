#include "stdafx.h"
#include "Input.h"
#include <conio.h>
#include <Windows.h>
#include "Soldier.h"

Input::Input(MessageLog* _mLog, TaskBuffer* _tBuffer)
{
	mLog = _mLog;
	tBuffer = _tBuffer;
	LOG("Input Objected Constructed");
}

Input::Input(MessageLog * _mLog, TaskBuffer * _tBuffer, WorldObj * _player)
{
	mLog = _mLog;
	tBuffer = _tBuffer;
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
		createTaskWithObj("Move_Up", "MOVE", player);
	}
	if (A)
	{
		createTaskWithObj("Move_Left", "MOVE", player);
	}
	if (S)
	{
		createTaskWithObj("Move_Down", "MOVE", player);
	}
	if (D)
	{
		createTaskWithObj("Move_Right", "MOVE", player);
	}
	if (R) {
		//Soldier* soldier = nullptr;
		createTask("add_soldier", "MODIFY_POOL");
	}
	if (T) { //Failure check on fake task name
		createTaskWithObj("Move_Out", "MOVE", player);
	}
}

void Input::createTask(std::string task_name, std::string type)
{
	//maybe just pass in the string craeated
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status, type);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}

void Input::createTaskWithObj(std::string task_name, std::string type, WorldObj * _objToUpdate)
{
	//maybe just pass in the string craeated
	std::string task_status = "CREATED";
	Task* new_task = new Task(task_name, task_status, type, _objToUpdate);
	tBuffer->push(new_task);
	mLog->logMessage(new_task);
}



