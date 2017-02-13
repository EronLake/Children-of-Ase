#pragma once
#include "common.h"
#include "Containers.h"
#include "MemNode.h"
#include "MemoryHelper.h"

class MemoryTestSuite
{
public:
	MemoryTestSuite();
	~MemoryTestSuite();

	//this function runs all the tests below
	bool execute_tests();

	//---------------------------------------
	bool Containers_constructor_test();
	bool Containers_destructor_test();
	bool add_hero_test();
	bool add_livingObj_test();
	bool add_projectile_test();
	bool add_soldier_test();
	bool add_spl_soldier_test();
	bool add_worldObj_test();
	bool add_npc_test();
	bool add_texture_test();

	//---------------------------------------
	//memory node tests
	bool memNode_constructor_test();
	//bool memNode_constructor_test_2();
	bool memNode_destructor_test();
	bool hasNext_test();
	bool getNext_test();
	bool setNext_test();
	bool getAvailability_test();
	bool setAvailability_test();
	bool getBlockPointer_test();
	bool setBlockPointer_test();

	//---------------------------------------

	//------------------------------------
	//memory pool tests
	bool store_hero_test();
	bool store_soldier_test();
	bool store_projectile_test();
	bool store_spl_soldier_test();
	bool store_livingObj_test();
	bool store_worldObj_test();
	bool store_npc_test();

	bool memoryHelper_constructor_test();
	bool memoryHelper_destructor_test();
	bool init_pool_test();
	bool get_free_pool_size_test();
	bool destroy_pool_test();
	bool create_pool_test();
	bool destroy_MemNode_list_test();
	bool make_Available_test();
	bool find_available_block_test();
	

};