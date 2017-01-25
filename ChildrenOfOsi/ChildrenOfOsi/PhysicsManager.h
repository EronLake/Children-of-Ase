#pragma once
#include "stdafx.h"
#include "common.h"
#include "Player.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"

class PhysicsManager : public Manager {
public:
	PhysicsManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	~PhysicsManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;

	WorldObj* player;

};


