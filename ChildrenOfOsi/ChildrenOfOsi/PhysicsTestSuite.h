#pragma once
#include "common.h"

class PhysicsTestSuite
{

	
public:
	PhysicsTestSuite();
	~PhysicsTestSuite();

	bool execute_tests();
	bool test_movement();
	bool test_collision();

};

