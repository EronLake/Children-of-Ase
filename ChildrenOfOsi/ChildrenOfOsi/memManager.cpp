#include "stdafx.h"
#include "memManager.h"
#include "Pool.h"


memManager::memManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
/*create and initialize all of the pools*/
	hero_pool = create_pool(4096);
	hero_head = init_pool(hero_pool,32);

	livingObj_pool = create_pool(4096);
	livingObj_head = init_pool(livingObj_pool, 32);

	projectile_pool = create_pool(4096);
	projectile_head = init_pool(projectile_pool, 32);

	soldier_pool = create_pool(4096);
	soldier_head = init_pool(soldier_pool, 32);

	spl_soldier_pool = create_pool(4096);
	spl_soldier_head = init_pool(spl_soldier_pool, 32);

	worldObj_pool = create_pool(4096);
	worldObj_head = init_pool(worldObj_pool, 32);

	npc_pool = create_pool(4096);
	npc_head = init_pool(npc_pool, 32);

	LOG("memManager Object Constructed");
	
}


memManager::~memManager()
{
	destroy_pool(hero_pool);
	destroy_MemNode_list(hero_head);

	destroy_pool(livingObj_pool);
	destroy_MemNode_list(livingObj_head);

	destroy_pool(projectile_pool);
	destroy_MemNode_list(projectile_head);

	destroy_pool(soldier_pool);
	destroy_MemNode_list(soldier_head);

	destroy_pool(spl_soldier_pool);
	destroy_MemNode_list(spl_soldier_head);

	destroy_pool(worldObj_pool);
	destroy_MemNode_list(worldObj_head);

	destroy_pool(npc_pool);
	destroy_MemNode_list(npc_head);
	LOG("memManager Object Destroyed");

}

void memManager::register_manager()
{
	
	tBuffer->add_to_table("MODIFY_POOL", this);
	
}

void memManager::execute_task(Task* current_task)
{
	int result;
    if (current_task->name == "add_soldier") {
		add_soldier();
		result = 0;
		
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "add_hero") {
		//add_hero();
		result = 0;

		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "add_projectile") {
		//add_projectile();
		result = 0;

		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "add_spl_soldier") {
		//add_spl_soldier();
		result = 0;

		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "add_livingObj") {
		//add_livingObj();
		result = 0;

		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "add_worldObj") {
		//add_worldObj();
		result = 0;

		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "add_npc") {
		//add_npc();
		result = 0;

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

///*
void add_hero() {
	Hero* h = new(find_available_block(hero_head)) Hero();
}

void add_soldier() {
	Soldier* s = new(find_available_block(soldier_head)) Soldier();
	std::cout << "soldier created" << std::endl;
	std::cout << "soldier Address: " << s << std::endl;
}

void add_spl_soldier() {
	SplSoldier* spl = new(find_available_block(spl_soldier_head)) SplSoldier();
}

void add_livingObj() {
	LivingObj* lobj = new(find_available_block(livingObj_head)) LivingObj();
}

void add_worldObj() {
	WorldObj* wobj = new(find_available_block(worldObj_head)) WorldObj();
}

void add_projectile() {
	Projectile* p = new(find_available_block(projectile_head)) Projectile();
}

void add_npc() {
	NPC* npc = new(find_available_block(npc_head)) NPC();
}
//*/



