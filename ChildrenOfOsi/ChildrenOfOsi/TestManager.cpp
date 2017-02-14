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
	bool result = run_unit_tests();
	if (current_task->name == "Run_Unit_Tests") {
		if (result == true) {
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

bool render_unit_test() {
	return 0;
}

bool memory_unit_test() {
	return 0;
}

/*NOTE: txt file outputs are located in Header Files/Test Outputs*/
bool TestManager::run_unit_tests() {
    bool result = true;
    std::ofstream ofs;
	time_t t = time(0);   // get time now
	struct tm  now;
	localtime_s(&now, &t);

	/*Initialize time variables for test output file
	timestamps*/
	int year = now.tm_year + 1900;
    int month = now.tm_mon + 1;
	int day = now.tm_mday;
	int hour = now.tm_hour;
	if (hour > 12)
		hour -= 12;
	int minute = now.tm_min;

	/*Instantiations of test suite classes*/
	TaskBufferTestSuite* t_suite = new TaskBufferTestSuite();
	AudioTestSuite* a_suite = new AudioTestSuite();
	PhysicsTestSuite* p_suite = new PhysicsTestSuite();
	MemoryTestSuite* m_suite = new MemoryTestSuite();

///////////Your unit test function calls here/////////////
	bool a_test = a_suite->execute_tests();
	bool r_test = render_unit_test();
	bool m_test = m_suite->execute_tests();
	bool p_test = p_suite->execute_tests();
	bool t_test = t_suite->execute_tests();

	if (a_test) {
	    ofs.open ("audio_test.txt", std::ofstream::out | std::ofstream::app);

	    ofs << month << "/" << day << "/" << year << "   "<<hour << ":" << minute<<"   Audio manager unit test passed!" << endl;

	    ofs.close();
		
	}
	else {
		result = false;
		ofs.open ("audio_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Audio manager unit test failed!" << endl;

		ofs.close();

	}
	if (r_test) {
	    ofs.open ("render_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Render manager unit test passed!" << endl;

	    ofs.close();

	}
	else {
		result = false;
		ofs.open ("render_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Render manager unit test failed!" << endl;

		ofs.close();

	}
	if (m_test) {
	    ofs.open ("memory_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Memory manager unit test passed!" << endl;

	    ofs.close();

	}
	else {
		result = false;
		ofs.open ("memory_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Memory manager unit test failed!" << endl;

		ofs.close();

	}
	if (p_test) {
	    ofs.open ("physics_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Physics manager unit test passed!" << endl;

	    ofs.close();

	}
	else {
		result = false;
		ofs.open ("physics_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Physics manager unit test failed!" << endl;

		ofs.close();

	}
	if (t_test) {
	    ofs.open ("task_buffer_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Task buffer unit test passed!" << endl;

	    ofs.close();

	}
	else {
		result = false;
		ofs.open ("task_buffer_test.txt", std::ofstream::out | std::ofstream::app);

		ofs << month << "/" << day << "/" << year << "   " << hour << ":" << minute << "   Task buffer unit test failed!" << endl;

		ofs.close();

	}
	return result;
}
