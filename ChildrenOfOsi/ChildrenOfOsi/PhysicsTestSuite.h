#pragma once
#include "common.h"

class PhysicsTestSuite
{

	
public:
	PhysicsTestSuite();
	~PhysicsTestSuite();

	bool execute_test();
	bool test_movement();
	bool test_collision();

};

