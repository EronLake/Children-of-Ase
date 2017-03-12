#include "stdafx.h"
#include "MemoryTestSuite.h"



MemoryTestSuite::MemoryTestSuite()
{
	LOG("MemoryTestSuite Object Constructed");
}


MemoryTestSuite::~MemoryTestSuite()
{
	LOG("MemoryTestSuite Object Destroyed");
}

//this function runs all the tests below
bool MemoryTestSuite::execute_tests() 
{
	bool pass = true;
	if (Containers_constructor_test() == true) 
	{
		LOG("Containers_constructor_test: " << "PASS");
	}
	else
	{
		LOG("Containers_constructor_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (Containers_destructor_test() == true)
	{
		LOG("Containers_destructor_test: " << "PASS");
	}
	else
	{
		LOG("Containers_destructor_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (add_hero_test() == true)
	{
		LOG("add_hero_test: " << "PASS");
	}
	else
	{
		LOG("add_hero_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (add_livingObj_test() == true)
	{
		LOG("add_livingObj_test: " << "PASS");
	}
	else
	{
		LOG("add_livingObj_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (add_Attack_test() == true)
	{
		LOG("add_Attack_test: " << "PASS");
	}
	else
	{
		LOG("add_Attack_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (add_soldier_test() == true)
	{
		LOG("add_soldier_test: " << "PASS");
	}
	else
	{
		LOG("add_soldier_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (add_spl_soldier_test() == true)
	{
		LOG("add_spl_soldier_test: " << "PASS");
	}
	else
	{
		LOG("add_spl_soldier_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (add_worldObj_test() == true)
	{
		LOG("add_worldObj_test: " << "PASS");
	}
	else
	{
		LOG("add_worldObj_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (add_npc_test() == true)
	{
		LOG("add_npc_test: " << "PASS");
	}
	else
	{
		LOG("add_npc_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (add_texture_test() == true)
	{
		LOG("add_texture_test: " << "PASS");
	}
	else
	{
		LOG("add_texture_test: " << "FAIL");
		pass = false;
	}

	//////////////////////////////////////////////
	//////////////////////////////////////////////

	//---------------------------------------------------
	if (memNode_constructor_test() == true)
	{
		LOG("memNode_constructor_test: " << "PASS");
	}
	else
	{
		LOG("memNode_constructor_test: " << "FAIL");
		pass = false;
	}
	/*
	//---------------------------------------------------
	if (memNode_constructor_test_2() == true)
	{
		LOG("memNode_constructor_test_2: " << "PASS");
	}
	else
	{
		LOG("memNode_constructor_test_2: " << "FAIL");
		pass = false;
	}
	*/
	//---------------------------------------------------
	if (memNode_destructor_test() == true)
	{
		LOG("memNode_destructor_test: " << "PASS");
	}
	else
	{
		LOG("memNode_destructor_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (hasNext_test() == true)
	{
		LOG("hasNext_test: " << "PASS");
	}
	else
	{
		LOG("hasNext_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (getNext_test() == true)
	{
		LOG("getNext_test: " << "PASS");
	}
	else
	{
		LOG("getNext_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (setNext_test() == true)
	{
		LOG("setNext_test: " << "PASS");
	}
	else
	{
		LOG("setNext_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (getAvailability_test() == true)
	{
		LOG("getAvailability_test: " << "PASS");
	}
	else
	{
		LOG("getAvailability_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (setAvailability_test() == true)
	{
		LOG("setAvailability_test: " << "PASS");
	}
	else
	{
		LOG("setAvailability_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (getBlockPointer_test() == true)
	{
		LOG("getBlockPointer_test: " << "PASS");
	}
	else
	{
		LOG("getBlockPointer_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (setBlockPointer_test() == true)
	{
		LOG("setBlockPointer_test: " << "PASS");
	}
	else
	{
		LOG("setBlockPointer_test: " << "FAIL");
		pass = false;
	}

	//////////////////////////////////////////////
	//////////////////////////////////////////////

	//---------------------------------------------------
	if (memoryHelper_constructor_test() == true)
	{
		LOG("memoryHelper_constructor_test: " << "PASS");
	}
	else
	{
		LOG("memoryHelper_constructor_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (memoryHelper_destructor_test() == true)
	{
		LOG("memoryHelper_destructor_test: " << "PASS");
	}
	else
	{
		LOG("memoryHelper_destructor_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (store_hero_test() == true)
	{
		LOG("store_hero_test: " << "PASS");
	}
	else
	{
		LOG("store_hero_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (store_soldier_test() == true)
	{
		LOG("store_soldier_test: " << "PASS");
	}
	else
	{
		LOG("store_soldier_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (store_Attack_test() == true)
	{
		LOG("store_Attack_test: " << "PASS");
	}
	else
	{
		LOG("store_Attack_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (store_spl_soldier_test() == true)
	{
		LOG("store_spl_soldier_test: " << "PASS");
	}
	else
	{
		LOG("store_spl_soldier_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (store_livingObj_test() == true)
	{
		LOG("store_livingObj_test: " << "PASS");
	}
	else
	{
		LOG("store_livingObj_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (store_worldObj_test() == true)
	{
		LOG("store_worldObj_test: " << "PASS");
	}
	else
	{
		LOG("store_worldObj_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (store_npc_test() == true)
	{
		LOG("store_npc_test: " << "PASS");
	}
	else
	{
		LOG("store_npc_test: " << "FAIL");
		pass = false;
	}
	

	//---------------------------------------------------
	if (init_pool_test() == true)
	{
		LOG("init_pool_test: " << "PASS");
	}
	else
	{
		LOG("init_pool_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (get_free_pool_size_test() == true)
	{
		LOG("get_free_pool_size_test: " << "PASS");
	}
	else
	{
		LOG("get_free_pool_size_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (destroy_pool_test() == true)
	{
		LOG("destroy_pool_test: " << "PASS");
	}
	else
	{
		LOG("destroy_pool_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (create_pool_test() == true)
	{
		LOG("create_pool_test: " << "PASS");
	}
	else
	{
		LOG("create_pool_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (destroy_MemNode_list_test() == true)
	{
		LOG("destroy_MemNode_list_test: " << "PASS");
	}
	else
	{
		LOG("destroy_MemNode_list_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (make_Available_test() == true)
	{
		LOG("make_Available_test: " << "PASS");
	}
	else
	{
		LOG("make_Available_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (find_available_block_test() == true)
	{
		LOG("find_available_block_test: " << "PASS");
	}
	else
	{
		LOG("find_available_block_test: " << "FAIL");
		pass = false;
	}


	return pass;

}


//////////////////////////////////////////////////
//Tests for Containers.cpp 
//////////////////////////////////////////////////
bool MemoryTestSuite::Containers_constructor_test()
{
	Containers* test_container = new Containers();


	if (Containers::hero_table.size() >= 0 &&
		Containers::livingObj_table.size() >= 0 &&
		Containers::Attack_table.size() >= 0 &&
		Containers::soldier_table.size() == 0 &&
		Containers::spl_soldier_table.size() >= 0 &&
		Containers::worldObj_table.size() >= 0 &&
		Containers::npc_table.size() >= 0 &&
		Containers::texture_table.size() >= 0
		) 
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool MemoryTestSuite::Containers_destructor_test()
{
	return true;
}


bool MemoryTestSuite::add_hero_test()
{
	bool pass = false;

	std::string hero_name = "test_hero";
	Hero* hero_value = new Hero();

	//called add_hero()
	Containers::add_hero(hero_name, hero_value);

	if (Containers::hero_table.count(hero_name) == 1)
	{
		pass = true;
		Containers::hero_table.erase(hero_name);
		delete hero_value;
	}
	
	if(Containers::hero_table.count(hero_name) == 0)
	{
		return pass;
	}
	else
	{
		LOG("TESTING ERROR: did not remove test_hero from table");
	}

}



bool MemoryTestSuite::add_livingObj_test()
{
	bool pass = false;

	std::string living_obj_name = "test_living_obj";
	LivingObj* living_obj_value = new LivingObj();

	//called add_hero()
	Containers::add_livingObj(living_obj_name, living_obj_value);

	if (Containers::livingObj_table.count(living_obj_name) == 1)
	{
		pass = true;
		Containers::livingObj_table.erase(living_obj_name);
		delete living_obj_value;
	}

	if (Containers::livingObj_table.count(living_obj_name) == 0)
	{
		return pass;
	}
	else
	{
		LOG("TESTING ERROR: did not remove test_living_obj from table");
	}

}




bool MemoryTestSuite::add_Attack_test()
{
	bool pass = false;

	std::string Attack_name = "test_Attack";
	Attack* Attack_value = new Attack();

	//called add_hero()
	Containers::add_Attack(Attack_name, Attack_value);

	if (Containers::Attack_table.count(Attack_name) == 1)
	{
		pass = true;
		Containers::Attack_table.erase(Attack_name);
		delete Attack_value;
	}

	if (Containers::Attack_table.count(Attack_name) == 0)
	{
		return pass;
	}
	else
	{
		LOG("TESTING ERROR: did not remove test_Attack from table");
		return false;
	}

}



bool MemoryTestSuite::add_soldier_test()
{
	bool pass = false;

	std::string soldier_name = "test_soldier";
	Soldier* soldier_value = new Soldier();

	//called add_hero()
	Containers::add_soldier(soldier_name, soldier_value);

	if (Containers::soldier_table.count(soldier_name) == 1)
	{
		pass = true;
		Containers::soldier_table.erase(soldier_name);
		delete soldier_value;
	}

	if (Containers::soldier_table.count(soldier_name) == 0)
	{
		return pass;
	}
	else
	{
		LOG("TESTING ERROR: did not remove test_soldier from table");
	}
}



bool MemoryTestSuite::add_spl_soldier_test()
{
	bool pass = false;

	std::string spl_soldier_name = "test_spl_soldier";
	SplSoldier* spl_soldier_value = new SplSoldier();

	//called add_hero()
	Containers::add_spl_soldier(spl_soldier_name, spl_soldier_value);

	if (Containers::spl_soldier_table.count(spl_soldier_name) == 1)
	{
		pass = true;
		Containers::spl_soldier_table.erase(spl_soldier_name);
		delete spl_soldier_value;
	}

	if (Containers::spl_soldier_table.count(spl_soldier_name) == 0)
	{
		return pass;
	}
	else
	{
		LOG("TESTING ERROR: did not remove test_spl_soldier from table");
	}

}
bool MemoryTestSuite::add_worldObj_test()
{
	bool pass = false;

	std::string worldObj_name = "test_worldObj";
	WorldObj* worldObj_value = new WorldObj();

	//called add_hero()
	Containers::add_worldObj(worldObj_name, worldObj_value);

	if (Containers::worldObj_table.count(worldObj_name) == 1)
	{
		pass = true;
		Containers::worldObj_table.erase(worldObj_name);
		delete worldObj_value;
	}

	if (Containers::worldObj_table.count(worldObj_name) == 0)
	{
		return pass;
	}
	else
	{
		LOG("TESTING ERROR: did not remove test_worldObj from table");
	}
}
bool MemoryTestSuite::add_npc_test()
{
	bool pass = false;

	std::string npc_name = "test_npc";
	NPC* npc_value = new NPC();

	//called add_hero()
	Containers::add_npc(npc_name, npc_value);

	if (Containers::npc_table.count(npc_name) == 1)
	{
		pass = true;
		Containers::npc_table.erase(npc_name);
		delete npc_value;
	}

	if (Containers::npc_table.count(npc_name) == 0)
	{
		return pass;
	}
	else
	{
		LOG("TESTING ERROR: did not remove test_npc from table");
	}
}

bool MemoryTestSuite::add_texture_test()
{
	bool pass = false;

	std::string texture_name = "test_texture";
	Texture* texture_value = new Texture();

	//called add_hero()
	Containers::add_texture(texture_name, texture_value);

	if (Containers::texture_table.count(texture_name) == 1)
	{
		pass = true;
		Containers::texture_table.erase(texture_name);
		delete texture_value;
	}

	if (Containers::texture_table.count(texture_name) == 0)
	{
		return pass;
	}
	else
	{
		LOG("TESTING ERROR: did not remove test_texture from table");
	}
}

//////////////////////////////////////////////////
//-----------------------------------------------
//////////////////////////////////////////////////


bool MemoryTestSuite::memNode_constructor_test()
{
	MemNode* test_mem_node = new MemNode();

	MemNode* next;
	bool is_available;
	void* block_pointer;

	if (test_mem_node->getNext() == NULL &&
		test_mem_node->getAvailability() == true &&
		test_mem_node->getBlockPointer() == NULL
		)
	{
		delete test_mem_node;
		return true;
	}
	else
	{
		delete test_mem_node;
		return false;
	}

}

/*
bool MemoryTestSuite::memNode_constructor_test_2()
{
	return false;
	//MemNode(const MemNode& orig);
}
*/


bool MemoryTestSuite::memNode_destructor_test() {
	return true;
}



bool MemoryTestSuite::hasNext_test()
{
	bool pass = true;

	MemNode* test_mem_node = new MemNode();

	if (test_mem_node->hasNext() == true) {
		pass = false;
	}

	MemNode* test_mem_node2 = new MemNode();
	test_mem_node->setNext(test_mem_node2);

	if (test_mem_node->hasNext() == false) {
		pass = false;
	}

	delete test_mem_node;
	delete test_mem_node2;
	return pass;
}



bool MemoryTestSuite::getNext_test()
{
	bool pass = true;

	MemNode* test_mem_node = new MemNode();

	if (test_mem_node->getNext() != NULL) {
		pass = false;
	}

	MemNode* test_mem_node2 = new MemNode();
	test_mem_node->setNext(test_mem_node2);

	if (test_mem_node->getNext() != test_mem_node2) {
		pass = false;
	}

	delete test_mem_node;
	delete test_mem_node2;
	return pass;
}



bool MemoryTestSuite::setNext_test()
{
	bool pass = true;

	MemNode* test_mem_node = new MemNode();
	MemNode* test_mem_node2 = new MemNode();

	test_mem_node->setNext(test_mem_node2);

	if (test_mem_node->getNext() != test_mem_node2) {
		pass = false;
	}

	delete test_mem_node;
	delete test_mem_node2;
	return pass;

}



bool MemoryTestSuite::getAvailability_test()
{
	bool pass = true;

	MemNode* test_mem_node = new MemNode();

	if (test_mem_node->getAvailability() == false) {
		pass = false;
	}

	test_mem_node->setAvailability(false);

	if (test_mem_node->getAvailability() == true) {
		pass = false;
	}

	delete test_mem_node;
	return pass;

}



bool MemoryTestSuite::setAvailability_test()
{
	bool pass = true;

	MemNode* test_mem_node = new MemNode();

	test_mem_node->setAvailability(false);

	if (test_mem_node->getAvailability() == true) {
		pass = false;
	}

	test_mem_node->setAvailability(true);

	if (test_mem_node->getAvailability() == false) {
		pass = false;
	}

	delete test_mem_node;
	return pass;
}



bool MemoryTestSuite::getBlockPointer_test()
{
	bool pass = true;

	MemNode* test_mem_node = new MemNode();

	if (test_mem_node->getBlockPointer() != NULL) {
		pass = false;
	}
	//allocte memory for block pointer
	void* test_blk_ptr = malloc(sizeof(int) * 5);
	test_mem_node->setBlockPointer(test_blk_ptr);

	if (test_mem_node->getBlockPointer() != test_blk_ptr) {
		pass = false;
	}

	delete test_mem_node;
	free(test_blk_ptr);
	return pass;
}



bool MemoryTestSuite::setBlockPointer_test()
{
	bool pass = true;

	MemNode* test_mem_node = new MemNode();
	//allocte memory for block pointer
	void* test_blk_ptr = malloc(sizeof(int) * 5);

	test_mem_node->setBlockPointer(test_blk_ptr);

	if (test_mem_node->getBlockPointer() != test_blk_ptr) {
		pass = false;
	}

	delete test_mem_node;
	free(test_blk_ptr);
	return pass;
}

//////////////////////////////////////////////////
//------------------------------------------------
//////////////////////////////////////////////////

bool MemoryTestSuite::memoryHelper_constructor_test()
{
	return true;
}
bool MemoryTestSuite::memoryHelper_destructor_test()
{
	return true;
}

bool MemoryTestSuite::store_hero_test()
{	
	bool pass = true;
	MemoryHelper* test_memory_helper = new MemoryHelper();

	std::cout << "------------------------"<< test_memory_helper->store_hero("test_obj", 1, 2, true);


	if (Containers::hero_table.count("test_obj") != 1 ||
		Containers::hero_table["test_obj"] == NULL)
	{
		pass = false;
	}

	Containers::hero_table.erase("test_obj");
	delete test_memory_helper;
	return pass;

}
bool MemoryTestSuite::store_soldier_test()
{
	bool pass = true;
	
	MemoryHelper* test_memory_helper = new MemoryHelper();
	
	test_memory_helper->store_soldier("test_obj", 1, 2, true);
	
	if (Containers::soldier_table.count("test_obj") != 1)
	{
		pass = false;
	}

	Containers::hero_table.erase("test_obj");
	delete test_memory_helper;
	
	return pass;
}
bool MemoryTestSuite::store_Attack_test()
{
	bool pass = true;

	MemoryHelper* test_memory_helper = new MemoryHelper();

	test_memory_helper->store_Attack("test_obj", 1, 2, true);

	if (Containers::Attack_table.count("test_obj") != 1)
	{
		pass = false;
	}

	Containers::Attack_table.erase("test_obj");
	delete test_memory_helper;

	return pass;
}
bool MemoryTestSuite::store_spl_soldier_test()
{
	bool pass = true;

	MemoryHelper* test_memory_helper = new MemoryHelper();

	test_memory_helper->store_spl_soldier("test_obj", 1, 2, true);

	if (Containers::spl_soldier_table.count("test_obj") != 1)
	{
		pass = false;
	}

	Containers::spl_soldier_table.erase("test_obj");
	delete test_memory_helper;

	return pass;
}
bool MemoryTestSuite::store_livingObj_test()
{
	bool pass = true;

	MemoryHelper* test_memory_helper = new MemoryHelper();

	test_memory_helper->store_livingObj("test_obj", 1, 2, true);

	if (Containers::livingObj_table.count("test_obj") != 1)
	{
		pass = false;
	}

	Containers::livingObj_table.erase("test_obj");
	delete test_memory_helper;

	return pass;
}
bool MemoryTestSuite::store_worldObj_test()
{
	bool pass = true;

	MemoryHelper* test_memory_helper = new MemoryHelper();

	test_memory_helper->store_worldObj("test_obj", 1, 2, true);

	if (Containers::worldObj_table.count("test_obj") != 1)
	{
		pass = false;
	}

	Containers::worldObj_table.erase("test_obj");
	delete test_memory_helper;

	return pass;
}
bool MemoryTestSuite::store_npc_test()
{
	bool pass = true;

	MemoryHelper* test_memory_helper = new MemoryHelper();

	test_memory_helper->store_npc("test_obj", 1, 2, true);

	if (Containers::npc_table.count("test_obj") != 1)
	{
		pass = false;
	}

	Containers::npc_table.erase("test_obj");
	delete test_memory_helper;

	return pass;
}

//--------------------------------------------

bool MemoryTestSuite::get_free_pool_size_test()
{
	bool pass = true;

	MemoryHelper* test_memory_helper = new MemoryHelper();
	MemoryPool* test_pool = test_memory_helper->create_pool(4096);

	MemNode* test_head = new MemNode();
	void* test_next = (void*)test_pool->next;
	test_head->setAvailability(true);
	test_head->setBlockPointer(test_next);
	test_pool->next += 32;

	LOG(test_memory_helper->get_free_pool_size(test_pool));
	if (test_memory_helper->get_free_pool_size(test_pool) != 4064)
	{
		pass = false;
	}

	delete test_memory_helper;
	delete test_pool;
	delete test_head;

	return pass;

}


//--------------------------------------------

bool MemoryTestSuite::init_pool_test()
{
	bool pass = true;

	MemoryHelper* test_memory_helper = new MemoryHelper();
	MemoryPool* test_pool = test_memory_helper->create_pool(4096);
	MemNode* test_head = test_memory_helper->init_pool(test_pool, 32);

	test_pool->next = (char*)test_head->getBlockPointer();
	while (test_pool->next != test_pool->end)
	{
		if (test_head->getAvailability() != true ||
			test_head->getNext() == NULL ||
			test_head->getBlockPointer() == NULL)
		{
			pass = false;
		}
		test_pool->next += 32;
	}
		
	delete test_memory_helper;
	delete test_pool;
	delete test_head;

	return pass;
}

bool MemoryTestSuite::destroy_pool_test()
{
	bool pass = true;

	MemoryHelper* test_memory_helper = new MemoryHelper();
	MemoryPool* test_pool = test_memory_helper->create_pool(4096);
	MemNode* test_head = test_memory_helper->init_pool(test_pool, 32);


	test_memory_helper->destroy_pool(test_pool);

	if (test_pool->next != NULL || test_pool->end != NULL)
	{
		pass = false;
	}

	delete test_memory_helper;
	delete test_head;

	return pass;

}
bool MemoryTestSuite::create_pool_test()
{

	bool pass = true;

	MemoryHelper* test_memory_helper = new MemoryHelper();
	MemoryPool* test_pool = test_memory_helper->create_pool(4096);


	if (test_pool->next != (char*)&test_pool[1] ||
		test_pool->end != test_pool->next + 4096 ||
		test_pool->pool_size != 4096
		)
	{
		pass = false;
	}

	delete test_memory_helper;
	delete test_pool;

	return pass;

}

bool MemoryTestSuite::destroy_MemNode_list_test()
{
	return true;
}

bool MemoryTestSuite::make_Available_test()
{
	std::string key = "";
	bool pass = true;

	MemoryHelper* test_memory_helper = new MemoryHelper();
	MemoryPool* test_pool = test_memory_helper->create_pool(4096);
	MemNode* test_head = test_memory_helper->init_pool(test_pool, 32);

	test_memory_helper->make_Available(test_head, test_pool, key);

	test_pool->next = (char*)test_head->getBlockPointer();
	while (test_pool->next != test_pool->end)
	{
		if (test_head->getAvailability() != true)
		{
			pass = false;
		}
		test_head = test_head->getNext();
		test_pool->next += 32;
	}

	delete test_memory_helper;
	delete test_pool;
	delete test_head;

	return pass;

}
bool MemoryTestSuite::find_available_block_test()
{
	std::string key = "";
	bool pass = true;
	
	MemoryHelper* test_memory_helper = new MemoryHelper();
	MemoryPool* test_pool = test_memory_helper->create_pool(4096);

	void* test_block = test_memory_helper->find_available_block(memManager::hero_head, key);

	if (test_block == NULL)
	{
		pass = false;
	}

	delete test_memory_helper;
	delete test_pool;

	return pass;
	
}

