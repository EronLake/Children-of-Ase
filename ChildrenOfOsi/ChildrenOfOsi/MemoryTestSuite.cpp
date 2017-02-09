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
	if (add_projectile_test() == true)
	{
		LOG("add_projectile_test: " << "PASS");
	}
	else
	{
		LOG("add_projectile_test: " << "FAIL");
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
	if (texture_npc_test() == true)
	{
		LOG("texture_npc_test: " << "PASS");
	}
	else
	{
		LOG("texture_npc_test: " << "FAIL");
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
		Containers::projectile_table.size() >= 0 &&
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

	std::string hero_name = "_test_hero";
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




bool MemoryTestSuite::add_projectile_test()
{
	bool pass = false;

	std::string projectile_name = "test_projectile";
	Projectile* projectile_value = new Projectile();

	//called add_hero()
	Containers::add_projectile(projectile_name, projectile_value);

	if (Containers::projectile_table.count(projectile_name) == 1)
	{
		pass = true;
		Containers::projectile_table.erase(projectile_name);
		delete projectile_value;
	}

	if (Containers::projectile_table.count(projectile_name) == 0)
	{
		return pass;
	}
	else
	{
		LOG("TESTING ERROR: did not remove test_projectile from table");
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

bool MemoryTestSuite::texture_npc_test()
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

/*
bool MemoryTestSuite::memNode_constructor_test()
{
	MemNode();

}
bool MemoryTestSuite::memNode_constructor_test_2()
{
	MemNode(const MemNode& orig);
}



bool MemoryTestSuite::memNode_destructor_test() {

}



bool MemoryTestSuite::hasNext_test()
{
	bool hasNext();
}



bool MemoryTestSuite::getNext_test()
{
	MemNode* getNext();
}



bool MemoryTestSuite::setNext_test()
{
	void setNext(MemNode* newNext);
}



bool MemoryTestSuite::getAvailability_test()
{
	bool getAvailability();

}



bool MemoryTestSuite::setAvailability_test()
{
	void setAvailability(bool avail);
}



bool MemoryTestSuite::getBlockPointer_test()
{
	void* getBlockPointer();
}



void MemoryTestSuite::setBlockPointer_test()
{
	void setBlockPointer(void* ptr);
}
*/
