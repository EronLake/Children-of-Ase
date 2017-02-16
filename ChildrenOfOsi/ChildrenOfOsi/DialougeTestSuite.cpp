#include "stdafx.h"
#include "DialougeTestSuite.h"



DialougeTestSuite::DialougeTestSuite()
{
}


DialougeTestSuite::~DialougeTestSuite()
{
}

bool DialougeTestSuite::execute_tests()
{
	bool pass = true;
	if (DialogueHelper_constructor_test() == true)
	{
		LOG("DialogueHelper_constructor_test: " << "PASS");
	}
	else
	{
		LOG("DialogueHelper_constructor_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (DialogueHelper_destructor_test() == true)
	{
		LOG("DialogueHelper_destructor_test: " << "PASS");
	}
	else
	{
		LOG("DialogueHelper_destructor_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (choose_conv_pt_test() == true)
	{
		LOG("choose_conv_pt_test: " << "PASS");
	}
	else
	{
		LOG("choose_conv_pt_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (choose_reply_test() == true)
	{
		LOG("choose_reply_test: " << "PASS");
	}
	else
	{
		LOG("choose_reply_test: " << "FAIL");
		pass = false;
	}

	return pass;

}

//////////////////////////////////////////////////
//Tests for Dialogue.cpp 
//////////////////////////////////////////////////

bool DialougeTestSuite::DialogueHelper_constructor_test()
{
	return false;
}

bool DialougeTestSuite::DialogueHelper_destructor_test()
{
	return true;
}

bool DialougeTestSuite::choose_conv_pt_test()
{
	bool pass = false;

	DialogueHelper* test_helper = new DialogueHelper();

	std::vector<std::string> test_dialog_pt = { "what", "variable" };

	//called test_function()
	std::vector<std::string> test_conv_pt = test_helper->choose_conv_pt(test_dialog_pt);
	for (int i = 0; i < test_helper->get_possible_conv_pts().size(); i++) {
		if(test_helper->get_possible_conv_pts()[i] == test_conv_pt)
		{
			pass = true;
		}
	}

	return pass;
}

bool DialougeTestSuite::choose_reply_test()
{
	bool pass = false;

	DialogueHelper* test_helper = new DialogueHelper();

	std::vector<std::string> test_dialog_pt = { "what", "variable" };

	//called test_function()
	std::vector<std::string> test_conv_pt = test_helper->choose_reply_pt(test_dialog_pt);
	if (test_conv_pt[0] == test_dialog_pt[0])
	{
		pass = true;
	}

	return pass;
}