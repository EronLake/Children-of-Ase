#include "stdafx.h"
#include "Containers.h"


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
void Containers::add_projectile(std::string key, Projectile* value)
{
	projectile_table[key] = value;
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
	texture_table[key] = value;
}


//need to declare tables in global scope before other functions can use them
//should eventually be moved to main
std::unordered_map<std::string, Hero*> Containers::hero_table;
std::unordered_map<std::string, LivingObj*> Containers::livingObj_table;
std::unordered_map<std::string, Projectile*> Containers::projectile_table;
std::unordered_map<std::string, Soldier*> Containers::soldier_table;
std::unordered_map<std::string, SplSoldier*> Containers::spl_soldier_table;
std::unordered_map<std::string, WorldObj*> Containers::worldObj_table;
std::unordered_map<std::string, NPC*> Containers::npc_table;
std::unordered_map<std::string, Texture*> Containers::texture_table;