#include "stdafx.h"
#include "TestManager.h"
#include <fstream>
#include <ctime>
#include <iostream>


TestManager::TestManager(MessageLog * _mLog, TaskBuffer * _tBuffer) : Manager(_mLog, _tBuffer)
{
	LOG("RenderManager W/QT Object Constructed");
	run_unit_tests();
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

/*Placeholder definitions for unit tests.
Only for purpose of testing test manager while people
work on their unit tests.*/
int audio_unit_test() {
	return 0;

}

int render_unit_test() {
	return 0;
}

int memory_unit_test() {
	return 0;
}

int task_buffer_unit_test() {
	return 1;
}

int physics_unit_test() {
	return 1;
}

/*NOTE: txt file outputs are located in Header Files/Test Outputs*/
int TestManager::run_unit_tests() {
    int result = 0;
    std::ofstream ofs;
	time_t t = time(0);   // get time now
	struct tm  now;
	localtime_s(&now, &t);

	/*Initialize time variables for test output file
	timestamps*/
	int year = now.tm_year + 1900;
    int month = now.tm_mon + 1;
	int day = now.tm_mday;
	int hour = now.tm_hour - 12;
	int minute = now.tm_min;

///////////Your unit test function calls here/////////////
	int a_test = audio_unit_test();
	int r_test = render_unit_test();
	int m_test = memory_unit_test();
	int p_test = physics_unit_test();
	int t_test = task_buffer_unit_test();

	if (a_test == 0) {
	    ofs.open ("audio_test.txt", std::ofstream::out | std::ofstream::app);

	    ofs << month << "/" << day << "/" << year << "   "<<hour << ":" << minute<<"   Audio manager unit test passed!" << endl;

	    ofs.close();
		
	}
	else {
		result = 1;
		ofs.open ("audio_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Audio manager unit test failed!" << endl;

		ofs.close();

	}
	if (r_test == 0) {
	    ofs.open ("render_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Render manager unit test passed!" << endl;

	    ofs.close();

	}
	else {
		result = 1;
		ofs.open ("render_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Render manager unit test failed!" << endl;

		ofs.close();

	}
	if (m_test == 0) {
	    ofs.open ("memory_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Memory manager unit test passed!" << endl;

	    ofs.close();

	}
	else {
		result = 1;
		ofs.open ("memory_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Memory manager unit test failed!" << endl;

		ofs.close();

	}
	if (p_test == 0) {
	    ofs.open ("physics_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Physics manager unit test passed!" << endl;

	    ofs.close();

	}
	else {
		result = 1;
		ofs.open ("physics_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Physics manager unit test failed!" << endl;

		ofs.close();

	}
	if (t_test == 0) {
	    ofs.open ("task_buffer_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Task buffer unit test passed!" << endl;

	    ofs.close();

	}
	else {
		result = 1;
		ofs.open ("task_buffer_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Task buffer unit test failed!" << endl;

		ofs.close();

	}
	return result;
}
