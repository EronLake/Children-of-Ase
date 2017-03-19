#include "stdafx.h"
//#include "memManager.h"
//#include "MemoryPool.h"
#include "ChildrenOfOsi.h"
#include "MemoryHelper.h"
#include "Tag.h"



memManager::memManager(MessageLog* _mLog, TaskBuffer* _tBuffer)
	: Manager(_mLog, _tBuffer)
{
/*create and initialize all of the pools*/

	memHelper = new MemoryHelper();

	hero_pool = memHelper->create_pool(sizeof(Hero) * 32);
	hero_head = memHelper->init_pool(hero_pool, sizeof(Hero)*2);

	livingObj_pool = memHelper->create_pool(sizeof(LivingObj) * 64);
	livingObj_head = memHelper->init_pool(livingObj_pool, sizeof(LivingObj)*2);

	Attack_pool = memHelper->create_pool(sizeof(Attack) * 256);
	Attack_head = memHelper->init_pool(Attack_pool, sizeof(Attack)*4);

	soldier_pool = memHelper->create_pool(sizeof(Soldier) * 64);
	soldier_head = memHelper->init_pool(soldier_pool, sizeof(Soldier)*2);

	spl_soldier_pool = memHelper->create_pool(sizeof(SplSoldier) * 64);
	spl_soldier_head = memHelper->init_pool(spl_soldier_pool, sizeof(SplSoldier)*2);

	worldObj_pool = memHelper->create_pool(sizeof(WorldObj)*456);
	worldObj_head = memHelper->init_pool(worldObj_pool, sizeof(WorldObj)*2);

	npc_pool = memHelper->create_pool(sizeof(NPC) * 64);
	npc_head = memHelper->init_pool(npc_pool, sizeof(NPC)*2);

	texture_pool = memHelper->create_pool(sizeof(Texture) * 32);
	texture_head = memHelper->init_pool(texture_pool, sizeof(Texture));

	oya_memory_pool = memHelper->create_pool(sizeof(Memory) * 40);
	oya_memory_head = memHelper->init_pool(oya_memory_pool, sizeof(Memory));
	memHelper->fill_mem_pool(oya_memory_head, OYA);

	yemoja_memory_pool = memHelper->create_pool(sizeof(Memory) * 40);
	yemoja_memory_head = memHelper->init_pool(yemoja_memory_pool, sizeof(Memory));
	memHelper->fill_mem_pool(yemoja_memory_head, YEMOJA);

	oshosi_memory_pool = memHelper->create_pool(sizeof(Memory) * 40);
	oshosi_memory_head = memHelper->init_pool(oshosi_memory_pool, sizeof(Memory));
	memHelper->fill_mem_pool(oshosi_memory_head, OSHOSI);

	ogun_memory_pool = memHelper->create_pool(sizeof(Memory) * 40);
	ogun_memory_head = memHelper->init_pool(ogun_memory_pool, sizeof(Memory));
	memHelper->fill_mem_pool(ogun_memory_head, OGUN);

	shango_memory_pool = memHelper->create_pool(sizeof(Memory) * 40);
	shango_memory_head = memHelper->init_pool(shango_memory_pool, sizeof(Memory));
	memHelper->fill_mem_pool(shango_memory_head, SHANGO);

	action_pool = memHelper->create_pool(sizeof(Action) * 200);
	action_head = memHelper->init_pool(action_pool, sizeof(Action));

	tag_pool = memHelper->create_pool(sizeof(Tag) * 32);
	tag_head = memHelper->init_pool(tag_pool, sizeof(Tag) * 2);

	conv_point_pool = memHelper->create_pool(sizeof(ConversationPoint) * 32);
	conv_point_head = memHelper->init_pool(conv_point_pool, sizeof(ConversationPoint) * 2);


	task_map["Add_Hero"] = &MemoryHelper::store_hero;
	task_map["Add_LivingObj"] = &MemoryHelper::store_livingObj;
	task_map["Add_NPC"] = &MemoryHelper::store_npc;
	task_map["Add_Attack"] = &MemoryHelper::store_Attack;
	task_map2["New_Attack"] = &MemoryHelper::new_Attack;
	task_map["Add_Soldier"] = &MemoryHelper::store_soldier;
	task_map["Add_Spl_Soldier"] = &MemoryHelper::store_spl_soldier;
	task_map["Add_WorldObj"] = &MemoryHelper::store_worldObj;
	task_map["Add_Texture"] = &MemoryHelper::store_texture;
	//adds a hero memory so uses a different function ptr map
	task_map3["Add_Memory"] = &MemoryHelper::store_memory;
	//adds a hero memory so uses a different function ptr map
	task_map4["Add_Action"] = &MemoryHelper::store_action;
	task_map["Del_Attack"] = &MemoryHelper::del_Attack;
	task_map["Add_Tag"] = &MemoryHelper::store_tag;
	task_map["Add_Conv_Point"] = &MemoryHelper::store_conv_point;

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

	memHelper->destroy_pool(oya_memory_pool);
	memHelper->destroy_MemNode_list(oya_memory_head);

	memHelper->destroy_pool(yemoja_memory_pool);
	memHelper->destroy_MemNode_list(yemoja_memory_head);

	memHelper->destroy_pool(oshosi_memory_pool);
	memHelper->destroy_MemNode_list(oshosi_memory_head);

	memHelper->destroy_pool(ogun_memory_pool);
	memHelper->destroy_MemNode_list(ogun_memory_head);

	memHelper->destroy_pool(shango_memory_pool);
	memHelper->destroy_MemNode_list(shango_memory_head);

	memHelper->destroy_pool(action_pool);
	memHelper->destroy_MemNode_list(action_head);

	memHelper->destroy_pool(tag_pool);
	memHelper->destroy_MemNode_list(tag_head);

	memHelper->destroy_pool(conv_point_pool);
	memHelper->destroy_MemNode_list(conv_point_head);

	LOG("memManager Object Destroyed");

}

void memManager::register_manager()
{
	
	tBuffer->add_to_table("MODIFY_POOL", this);
	
}

void memManager::execute_task(Task* current_task)
{
	int result;
	WorldObj* obj = current_task->objToUpdate;
	std::string key = current_task->key;
	float xpos = current_task->arg1;
	float ypos = current_task->arg2;
	bool coll = current_task->arg3;
	//also used fot the hero_number and action utility
	int num = current_task->arg4;

	int mem_type = current_task->mem_type;
	int frames = current_task->frames;
	vector<NPC*> people = current_task->people;
	//cat also being used as exec_name
	std::string cat = current_task->cat;
	std::string cont = current_task->cont;
	std::string where = current_task->where;
	int why = current_task->why;
	int when = current_task->when;
//	int d = current_task->arg4;

	Hero* owner = current_task->owner;
	Hero* receiver = current_task->receiver;
	Hero* doer = current_task->doer;

	auto it = task_map.find(current_task->name);
	auto it2 = task_map2.find(current_task->name);
	auto it3 = task_map3.find(current_task->name);
	auto it4 = task_map4.find(current_task->name);
	if (it == task_map.end() && it2 == task_map2.end() && it3 == task_map3.end() && it4 == task_map4.end()) {
		result = 1;
		LOG("Error: Task '" << current_task->name << "' does not exist.");
	}
	else {
		//check if updating an existing object
		if (obj == nullptr && people.size() == 0) {
			result = (memHelper->*(it->second))(key, xpos, ypos, coll);
		}
		//check if adding a memory
		else if (people.size() == 0) {
			result = (memHelper->*(it2->second))(obj, num);
		}
		else if(owner)
		{
			result = (memHelper->*(it4->second))(key,num,why,owner,receiver, doer, cat);
		}
		else {
			result = (memHelper->*(it3->second))(key, num, mem_type,frames, people,cat,cont, where, why, when);
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

MemoryPool* memManager::oya_memory_pool = nullptr;
MemNode* memManager::oya_memory_head = nullptr;

MemoryPool* memManager::yemoja_memory_pool = nullptr;
MemNode* memManager::yemoja_memory_head = nullptr;

MemoryPool* memManager::oshosi_memory_pool = nullptr;
MemNode* memManager::oshosi_memory_head = nullptr;

MemoryPool* memManager::ogun_memory_pool = nullptr;
MemNode* memManager::ogun_memory_head = nullptr;

MemoryPool* memManager::shango_memory_pool = nullptr;
MemNode* memManager::shango_memory_head = nullptr;

MemoryPool* memManager::action_pool = nullptr;
MemNode* memManager::action_head = nullptr;

MemoryPool* memManager::tag_pool = nullptr;
MemNode* memManager::tag_head = nullptr;

MemoryPool* memManager::conv_point_pool = nullptr;
MemNode* memManager::conv_point_head = nullptr;