#include "stdafx.h"
#include "TestManager.h"
#include <fstream>
#include <ctime>
#include <iostream>


TestManager::TestManager(MessageLog * _mLog, TaskBuffer * _tBuffer) : Manager(_mLog, _tBuffer)
{
	LOG("RenderManager W/QT Object Constructed");
}

TestManager::~TestManager()
{
}

void TestManager::register_manager()
{
	tBuffer->add_to_table("TEST", this);
}

void TestManager::execute_task(Task* current_task)
{
	int result = run_unit_tests();
	if (current_task->name == "Run_Unit_Tests") {
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else
	{
		LOG("Error: Task name does not exist"); //perror?
	}
}

int TestManager::run_unit_tests() {
    int result = 0;
/*
    std::ofstream ofs;
	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	std::string year = now->tm_year + 1900;
    std::string month = now->tm_mon + 1;
	std::string day = now->tm_mday + 1900;
	ofs.open ("test_resutls/[timestamp]test.txt", std::ofstream::out | std::ofstream::app);

	ofs << year << month << day;

	ofs.close();
///////////Your unit test function calls here/////////////
	//int a_test = audio_unit_test();
	//int r_test = render_unit_test();
	//int m_test = memory_unit_test();
	//int p_test = physics_unit_test();
	//int t_test = task_buffer_unit_test();
	if (a_test == 0) {
	    ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);

	    ofs << "Audio manager unit test passed!";

	    ofs.close();
		
	}
	else {
		result = 1;
		ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);

		ofs << "Audio manager unit test failed!";

		ofs.close();

	}
	if (r_test == 0) {
	    ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);

	    ofs << "Render manager unit test passed!";

	    ofs.close();

	}
	else {
		result = 1;
		ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);

		ofs << "Render manager unit test failed!";

		ofs.close();

	}
	if (m_test == 0) {
	    ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);

	    ofs << "Memory manager unit test passed!";

	    ofs.close();

	}
	else {
		result = 1;
		ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);

		ofs << "Memory manager unit test failed!";

		ofs.close();

	}
	if (p_test == 0) {
	    ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);

	    ofs << "Physics manager unit test passed!";

	    ofs.close();

	}
	else {
		result = 1;
		ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);

		ofs << "Physics manager unit test failed!";

		ofs.close();

	}
	if (t_test == 0) {
	    ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);

	    ofs << "Task buffer manager unit test passed!";

	    ofs.close();

	}
	else {
		result = 1;
		ofs.open ("test.txt", std::ofstream::out | std::ofstream::app);

		ofs << "Task buffer manager unit test failed!";

		ofs.close();

	}
	*/
	return result;
}
