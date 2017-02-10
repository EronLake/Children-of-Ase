#pragma once
#include "common.h"
#include "Containers.h"

class MemoryTestSuite
{
public:
	MemoryTestSuite();
	~MemoryTestSuite();

	//this function runs all the tests below
	bool execute_tests();

	bool Containers_constructor_test();
	bool Containers_destructor_test();
	bool add_hero_test();
	bool add_livingObj_test();
	bool add_projectile_test();
	bool add_soldier_test();
	bool add_spl_soldier_test();
	bool add_worldObj_test();
	bool add_npc_test();
	bool texture_npc_test();

	//---------------------------------------
	/*
	bool memNode_constructor_test();
	bool memNode_constructor_test_2();
	bool memNode_destructor_test();
	bool hasNext_test();
	bool getNext_test();
	bool setNext_test();
	bool getAvailability_test();
	bool setAvailability_test();
	bool getBlockPointer_test();
	void setBlockPointer_test();
	*/

};