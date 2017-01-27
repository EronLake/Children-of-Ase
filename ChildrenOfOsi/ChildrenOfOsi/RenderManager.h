#pragma once
#include "stdafx.h"
#include "common.h"
#include "Player.h"
#include "MessageLog.h"
#include "TaskBuffer.h"
#include "Manager.h"
#include "RenderHelper.h"
class RenderManager : public Manager
{
public:
	RenderManager(MessageLog* _mLog, TaskBuffer* _tBuffer);
	RenderManager(MessageLog* _mLog, TaskBuffer* _tBuffer, QuadTree* _renderQuadTree);
	~RenderManager();

	virtual void register_manager() final;
	virtual void execute_task(Task* current_task) final;
private:
	//use this to communicate with render helper
	RenderHelper* renderHelper;
};

