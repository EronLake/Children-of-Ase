#include "stdafx.h"
#include "TaskBufferTestSuite.h"



TaskBufferTestSuite::TaskBufferTestSuite()
{
	LOG("TaskBufferTestSuite Object Constructed");
}


TaskBufferTestSuite::~TaskBufferTestSuite()
{
	LOG("TaskBufferTestSuite Object Destroyed");
}

bool TaskBufferTestSuite:: execute_tests() {
	bool pass = true;
	if (TaskBuffer_constructor_test() == true)
	{
		LOG("TaskBuffer_constructor_test: " << "PASS");
	}
	else
	{
		LOG("TaskBuffer_constructor_test: " << "FAIL");
		pass = false;
	}

	//--------------------------------------------------
	if (run_test() == true)
	{
		LOG("run_test: " << "PASS");
	}
	else
	{
		LOG("run_test: " << "FAIL");
		pass = false;
	}

	//--------------------------------------------------
	if (assignTask_test() == true)
	{
		LOG("assignTask_test: " << "PASS");
	}
	else
	{
		LOG("assignTask_test: " << "FAIL");
		pass = false;
	}

	//--------------------------------------------------
	if (isEmpty_test() == true)
	{
		LOG("isEmpty_test: " << "PASS");
	}
	else
	{
		LOG("isEmpty_test: " << "FAIL");
		pass = false;
	}

	//--------------------------------------------------
	if (empty_test() == true)
	{
		LOG("empty_test: " << "PASS");
	}
	else
	{
		LOG("empty_test: " << "FAIL");
		pass = false;
	}

	//--------------------------------------------------
	if (push_test() == true)
	{
		LOG("push_test: " << "PASS");
	}
	else
	{
		LOG("push_test: " << "FAIL");
		pass = false;
	}

	//--------------------------------------------------
	if (pop_test() == true)
	{
		LOG("pop_test: " << "PASS");
	}
	else
	{
		LOG("pop_test: " << "FAIL");
		pass = false;
	}

	//--------------------------------------------------
	if (TaskBuffer_destructor_test() == true)
	{
		LOG("TaskBuffer_destructor_test: " << "PASS");
	}
	else
	{
		LOG("TaskBuffer_destructor_test: " << "FAIL");
		pass = false;
	}

	//--------------------------------------------------
	return pass;
}

bool TaskBufferTestSuite::TaskBuffer_constructor_test()//Don't really know how to Test this out??? Update: Revised it to test constructor
{
	MessageLog* ML = new MessageLog();
	TaskBuffer* TB = new TaskBuffer(ML);
	delete(TB);
	delete(ML);
	return true;
}
bool TaskBufferTestSuite::TaskBuffer_destructor_test()
{
	
	return true;
}


bool TaskBufferTestSuite::isEmpty_test()
{
	bool pass = false;
	bool flag_1 = false;
	bool flag_2 = false;
	std::string test_1 = "test_1";
	std::string test_2 = "CREATED";
	std::string test_3 = "type_test";
	Task* test_task = new Task(test_1, test_2, test_3);
	MessageLog* ML = new MessageLog();
	TaskBuffer* TB = new TaskBuffer(ML);
	if (TB->isEmpty() == true)
	{
		flag_1 = true;
	}
	TB->push(test_task);
	if (TB->isEmpty() == false)
	{
		flag_2 = true;
	}
	if ((flag_1 == true) && (flag_2 == true))
	{
		pass = true;
	}
	TB->empty();
	delete(TB);
	delete(ML);
	
	return pass;
}
bool TaskBufferTestSuite::empty_test()
{
	bool pass = false;
	std::string test_1 = "test_1";
	std::string test_2 = "CREATED";
	std::string test_3 = "type_test";
	Task* test_task = new Task(test_1, test_2, test_3);
	MessageLog* ML = new MessageLog();
	TaskBuffer* TB = new TaskBuffer(ML);

	TB->push(test_task);
	TB->empty();
	if (TB->isEmpty() == true)
	{
		pass = true;
	}
	TB->empty();
	delete(TB);
	delete(ML);
	
	return pass;
}
bool TaskBufferTestSuite::push_test()
{
	bool pass = false;
	bool flag_1 = false;
	bool flag_2 = false;
	std::string test_1 = "test_1";
	std::string test_2 = "CREATED";
	std::string test_3 = "type_test";
	Task* test_task = new Task(test_1, test_2, test_3);
	MessageLog* ML = new MessageLog();
	TaskBuffer* TB = new TaskBuffer(ML);
	if (TB->isEmpty() == true)
	{
		flag_1 = true;
	}
	TB->push(test_task);
	if (TB->isEmpty() == false)
	{
		flag_2 = true;
	}
	if ((flag_1 == true) && (flag_2 == true))
	{
		pass = true;
	}
	TB->empty();
	delete(TB);
	delete(ML);
	
	return pass;
}
bool TaskBufferTestSuite::pop_test()
{
	bool pass = false;
	bool flag_1 = false;
	bool flag_2 = false;
	bool flag_3 = false;
	std::string test_1 = "test_1";
	std::string test_2 = "CREATED";
	std::string test_3 = "type_test";
	Task* test_task = new Task(test_1, test_2, test_3);
	MessageLog* ML = new MessageLog();
	TaskBuffer* TB = new TaskBuffer(ML);
	if (TB->isEmpty() == true)
	{
		flag_1 = true;
	}
	TB->push(test_task);
	if (TB->isEmpty() == false)
	{
		flag_2 = true;
	}
	Task* test_task_2 = TB->pop();
	if (TB->isEmpty() == true)
	{
		flag_3 = true;
	}
	if ((flag_1 == true) && (flag_2 == true) && (flag_3 == true))
	{
		pass = true;
	}
	TB->empty();
	delete(TB);
	delete(ML);
	
	return pass;
}

bool TaskBufferTestSuite::assignTask_test() //Not Super sure how to test this function out??? Update: Revised it to actually have a test condition
{
	bool pass = false;
	std::string test_1 = "test_1";
	std::string test_2 = "CREATED";
	std::string test_3 = "type_test";
	Task* test_task = new Task(test_1, test_2, test_3);
	MessageLog* ML = new MessageLog();
	TaskBuffer* TB = new TaskBuffer(ML);
	TB->assignTask(0,test_task);
	if (test_task->status == "WORKING")
	{
		pass = true;
	}
	TB->empty();
	delete(TB);
	delete(ML);
	
	return pass;
}

bool TaskBufferTestSuite::run_test()
{
	bool pass = false;
	std::string test_1 = "test_1";
	std::string test_2 = "CREATED";
	std::string test_3 = "type_test";
	Task* test_task = new Task(test_1, test_2, test_3);
	MessageLog* ML = new MessageLog();
	TaskBuffer* TB = new TaskBuffer(ML);
	ML->logMessage(test_task);
	TB->push(test_task);
	TB->run();
	if (TB->isEmpty() == true)
	{
		pass = true;
	}
	TB->empty();
	delete(TB);
	delete(ML);
	
	return pass;
}