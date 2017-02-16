#pragma once
#include "common.h"
#include "DialogueHelper.h"

class DialougeTestSuite
{
public:
	DialougeTestSuite();
	~DialougeTestSuite();


	//this function runs all the tests below
	bool execute_tests();

	//---------------------------------------
	bool DialogueHelper_constructor_test();
	bool DialogueHelper_destructor_test();
	bool choose_conv_pt_test();
	bool choose_reply_test();
	
};

