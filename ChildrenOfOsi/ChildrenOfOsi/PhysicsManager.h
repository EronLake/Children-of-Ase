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
public:
	PhysicsManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	PhysicsManager(MessageLog* _mLog, TaskBuffer* _tBuffer, QuadTree* _physicsQuadTree);
	~PhysicsManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

private:
	//use this to communicate with movement helper(needed to access quadtree for collision)
	typedef int (Movement::*fn_ptr)(WorldObj*);
	typedef std::map<std::string, fn_ptr> functionMapper;

    functionMapper task_map;
    functionMapper::const_iterator it;

	Movement* moveHelper;
};

