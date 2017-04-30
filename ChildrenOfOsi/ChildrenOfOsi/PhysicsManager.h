#pragma once
#include <map>
#include "stdafx.h"
#include "common.h"
#include "Player.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"
#include "Movement.h"

class PhysicsManager : public Manager {
private:
	typedef int (Movement::*fn_ptr)(WorldObj*);
	typedef std::map<std::string, fn_ptr> functionMapper;
    functionMapper task_map;
	Movement* moveHelper;

public:
	PhysicsManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	PhysicsManager(MessageLog* _mLog, TaskBuffer* _tBuffer, QuadTree* _physicsQuadTree, UniformGrid* _uniformGrid, RiverObj* _rivObj);
	~PhysicsManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;
};

