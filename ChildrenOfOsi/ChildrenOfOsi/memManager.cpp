#include "stdafx.h"
//#include "memManager.h"
//#include "MemoryPool.h"
#include "ChildrenOfOsi.h"
#include "MemoryHelper.h"



memManager::memManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
/*create and initialize all of the pools*/

	memHelper = new MemoryHelper();

	hero_pool = memHelper->create_pool(sizeof(Hero) * 8);
	hero_head = memHelper->init_pool(hero_pool, sizeof(Hero)*2);

	livingObj_pool = memHelper->create_pool(sizeof(LivingObj) * 64);
	livingObj_head = memHelper->init_pool(livingObj_pool, sizeof(LivingObj)*2);

	Attack_pool = memHelper->create_pool(sizeof(Attack) * 64);
	Attack_head = memHelper->init_pool(Attack_pool, sizeof(Attack)*4);

	soldier_pool = memHelper->create_pool(sizeof(Soldier) * 64);
	soldier_head = memHelper->init_pool(soldier_pool, sizeof(Soldier)*2);

	spl_soldier_pool = memHelper->create_pool(sizeof(SplSoldier) * 64);
	spl_soldier_head = memHelper->init_pool(spl_soldier_pool, sizeof(SplSoldier)*2);

	worldObj_pool = memHelper->create_pool(sizeof(WorldObj)*128);
	worldObj_head = memHelper->init_pool(worldObj_pool, sizeof(WorldObj)*2);

	npc_pool = memHelper->create_pool(sizeof(NPC) * 64);
	npc_head = memHelper->init_pool(npc_pool, sizeof(NPC));

	texture_pool = memHelper->create_pool(sizeof(Texture) * 32);
	texture_head = memHelper->init_pool(texture_pool, sizeof(Texture));


	task_map["Add_Hero"] = &MemoryHelper::store_hero;
	task_map["Add_LivingObj"] = &MemoryHelper::store_livingObj;
	task_map["Add_NPC"] = &MemoryHelper::store_npc;
	task_map["Add_Attack"] = &MemoryHelper::store_Attack;
	task_map2["New_Attack"] = &MemoryHelper::new_Attack;
	task_map2["New_Spin"] = &MemoryHelper::new_Spin;
	task_map["Add_Soldier"] = &MemoryHelper::store_soldier;
	task_map["Add_Spl_Soldier"] = &MemoryHelper::store_spl_soldier;
	task_map["Add_WorldObj"] = &MemoryHelper::store_worldObj;
	task_map["Add_Texture"] = &MemoryHelper::store_texture;
	task_map["Del_Attack"] = &MemoryHelper::del_Attack;

	LOG("memManager Object Constructed");
	
}


memManager::~memManager()
{
	memHelper->destroy_pool(hero_pool);
	memHelper->destroy_MemNode_list(hero_head);

	memHelper->destroy_pool(livingObj_pool);
	memHelper->destroy_MemNode_list(livingObj_head);

	memHelper->destroy_pool(Attack_pool);
	memHelper->destroy_MemNode_list(Attack_head);

	memHelper->destroy_pool(soldier_pool);
	memHelper->destroy_MemNode_list(soldier_head);

	memHelper->destroy_pool(spl_soldier_pool);
	memHelper->destroy_MemNode_list(spl_soldier_head);

	memHelper->destroy_pool(worldObj_pool);
	memHelper->destroy_MemNode_list(worldObj_head);

	memHelper->destroy_pool(npc_pool);
	memHelper->destroy_MemNode_list(npc_head);

	memHelper->destroy_pool(texture_pool);
	memHelper->destroy_MemNode_list(texture_head);

	LOG("memManager Object Destroyed");

}

void memManager::register_manager()
{
	
	tBuffer->add_to_table("MODIFY_POOL", this);
	
}

void memManager::execute_task(Task* current_task)
{
	int result;
	WorldObj* obj= current_task->objToUpdate;
	std::string key = current_task->key;
	float xpos = current_task->arg1;
	float ypos = current_task->arg2;
	bool coll = current_task->arg3;
	int num= current_task->arg4;
//	int d = current_task->arg4;

	auto it = task_map.find(current_task->name);
	auto it2 = task_map2.find(current_task->name);
	if (it == task_map.end() && it2 == task_map2.end()) {
		result = 1;
		LOG("Error: Task '" << current_task->name << "' does not exist.");
	}
	else {
		if (obj == nullptr) {
			result = (memHelper->*(it->second))(key, xpos, ypos, coll);
		}
		else {
			result = (memHelper->*(it2->second))(obj, num);
		}
	}

	if (result == 0) {
		current_task->updateStatus("COMPLETED");
	}
	else {
		current_task->updateStatus("FAILED");
	}
	this->send_result(current_task);


    /*if (current_task->name == "Add_Soldier") {
		store_soldier(xpos,ypos,coll);
		result = 0;
		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "Add_Hero") {
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
	else if (current_task->name == "Add_Attack") {
		//add_Attack();
		result = 0;

		if (result == 0) {
			current_task->updateStatus("COMPLETED");
		}
		else {
			current_task->updateStatus("FAILED");
		}
		this->send_result(current_task);
	}
	else if (current_task->name == "Add_Spl_Soldier") {
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
	else if (current_task->name == "Add_LivingObj") {
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
	else if (current_task->name == "Add_WorldObj") {
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
	else if (current_task->name == "Add_NPC") {
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
	}*/

}

/*This code fixes the stupid linker errors with the pool and head pointers.*/
/*Discovered that defining the vars in the memManager constructor is good 
but then the definitions are not recognized during compile time,causing the
linker errors.*/
MemoryPool* memManager::hero_pool = nullptr;
MemNode* memManager::hero_head = nullptr;

MemoryPool* memManager::livingObj_pool = nullptr;
MemNode* memManager::livingObj_head = nullptr;

MemoryPool* memManager::Attack_pool = nullptr;
MemNode* memManager::Attack_head = nullptr;

MemoryPool* memManager::soldier_pool = nullptr;
MemNode* memManager::soldier_head = nullptr;

MemoryPool* memManager::spl_soldier_pool = nullptr;
MemNode* memManager::spl_soldier_head = nullptr;

MemoryPool* memManager::worldObj_pool = nullptr;
MemNode* memManager::worldObj_head = nullptr;

MemoryPool* memManager::npc_pool = nullptr;
MemNode* memManager::npc_head = nullptr;

MemoryPool* memManager::texture_pool = nullptr;
MemNode* memManager::texture_head = nullptr;
