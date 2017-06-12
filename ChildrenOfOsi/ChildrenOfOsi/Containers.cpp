#include "stdafx.h"
#include "Containers.h"
#include "Rectangle.h"
#include "WorldObj.h"


Containers::Containers()
{
	LOG("Containers Object Constructed");
}


Containers::~Containers()
{
	LOG("Containers Object Destroyed");
}

void Containers::add_hero(std::string key, Hero* value)
{
	hero_table[key] = value;
}
void Containers::add_livingObj(std::string key, LivingObj* value)
{
	livingObj_table[key] = value;
}
void Containers::add_Attack(std::string key, Attack* value)
{
	Attack_table[key] = value;
}
void Containers::add_soldier(std::string key, Soldier* value)
{
	soldier_table[key] = value;
}
void Containers::add_spl_soldier(std::string key, SplSoldier* value)
{
	spl_soldier_table[key] = value;
}
void Containers::add_worldObj(std::string key, WorldObj* value)
{
	worldObj_table[key] = value;
}
void Containers::add_npc(std::string key, NPC* value)
{
	npc_table[key] = value;
}

void Containers::add_texture(std::string key, Texture* value)
{
	LOG(key << "/" << value);
	texture_table[key] = value;
}

void Containers::add_memory(std::string key, int hero_name, Memory* value)
{
	if (hero_name == OYA)
	{
		oya_memory_table[key] = value;
	}
	else if (hero_name == YEMOJA)
	{
		yemoja_memory_table[key] = value;
	}
	else if (hero_name == OSHOSI)
	{
		oshosi_memory_table[key] = value;
	}
	else if (hero_name == OGUN)
	{
		ogun_memory_table[key] = value;
	}
	else if (hero_name == SHANGO)
	{
		shango_memory_table[key] = value;
	}

}

void Containers::add_action(std::string key, Action* value)
{
	action_table[key] = value;
}

void Containers::add_tag(std::string key, Tag* t)
{
	tag_table[key] = t;
}

void Containers::add_conv_point(std::string key, ConversationPoint* c)
{
	conv_point_table[key] = c;
}


//need to declare tables in global scope before other functions can use them
//should eventually be moved to main
std::unordered_map<std::string, Hero*> Containers::hero_table;
std::unordered_map<std::string, LivingObj*> Containers::livingObj_table;
std::unordered_map<std::string, Attack*> Containers::Attack_table;
std::unordered_map<std::string, Soldier*> Containers::soldier_table;
std::unordered_map<std::string, SplSoldier*> Containers::spl_soldier_table;
std::unordered_map<std::string, WorldObj*> Containers::worldObj_table;
std::unordered_map<std::string, NPC*> Containers::npc_table;
std::unordered_map<std::string, Texture*> Containers::texture_table;
std::unordered_map<std::string, Memory*> Containers::oya_memory_table;
std::unordered_map<std::string, Memory*> Containers::yemoja_memory_table;
std::unordered_map<std::string, Memory*> Containers::oshosi_memory_table;
std::unordered_map<std::string, Memory*> Containers::ogun_memory_table;
std::unordered_map<std::string, Memory*> Containers::shango_memory_table;
std::unordered_map<std::string, Action*> Containers::action_table;
std::unordered_map<std::string, Tag*> Containers::tag_table;
std::unordered_map<std::string, ConversationPoint*> Containers::conv_point_table;

std::vector<std::vector<float>> Containers::getRects() {
	std::vector<std::vector<float>> ret;
	Rectangle r;
	for (auto it = Containers::worldObj_table.begin(); it != Containers::worldObj_table.end(); ++it) {
		r = (*it).second->body[0];
		ret.push_back({r.getX()/100,r.getY()/100,(r.getX()+r.getWidth())/100,(r.getY()+r.getHeight())/100});
	}
	return ret;
}
