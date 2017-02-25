#pragma once
#include "stdafx.h"
#include <map>
#include "common.h"
#include "Player.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"
#include "RenderHelper.h"
class RenderManager : public Manager
{
public:
	//use this to communicate with render helper
	//need this for map editor
	RenderHelper* renderHelper;

	RenderManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	RenderManager(MessageLog* _mLog, TaskBuffer* _tBuffer, QuadTree* _renderQuadTree);
	~RenderManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;
private:
	

	typedef int (RenderHelper::*fptr)(WorldObj*);
	typedef std::map<std::string, fptr> functionMapper;
	functionMapper task_map;

};

