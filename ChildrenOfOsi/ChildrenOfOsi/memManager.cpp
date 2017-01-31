#include "stdafx.h"
#include "memManager.h"
#include "Pool.h"


memManager::memManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
//	hero_pool = create_pool();
//	hero_head = init_pool(hero_pool,);
//  soldier_pool = create_pool();
//  soldier_head = init_pool(soldier_pool,);
//  tree_pool = create_pool();
//  tree_pool = init_pool(tree_pool,)
//  projectile_pool = create_pool();
//  projectile_head = init_pool(projectile_head,);
//  quest_pool = create_pool();
//  quest_head = init_pool(quest_pool,);
//  villager_pool = create_pool();
//  villager_head = init_pool(villager_pool,_;
//  rock_pool = create_pool();
//  rock_head = init_pool(rock_pool,);
//  ase_pool = create_pool();
//  ase_head = init_pool(ase_pool,);
//Need to add more pools
	LOG("memManager Object Constructed");
	
}


memManager::~memManager()
{
	
	LOG("memManager Object Destroyed");

}

void memManager::register_manager()
{
	
	tBuffer->add_to_table("CREATE_POOL", this);
	tBuffer->add_to_table("MODIFY_POOL", this);
	
}

void memManager::execute_task(Task* current_task)
{
	int result;
	MemoryPool* p = create_pool(4096);
	MemNode* m = init_pool(p, 32);
	if (current_task->name == "create_pool") {
		if(p != nullptr && m != nullptr)
	        result = 0;
		
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "destroy_pool") {
		destroy_pool(p);
		destroy_MemNode_list(m);
		result = 0;
		
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "add_to_pool") {
		void* f = find_available_block(m);
		result = 0;

		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "remove_from_pool") {
		void* f = make_Available(m,p,0);
		if(f != NULL)
		    result = 0;
		else 
			result = 1;

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



