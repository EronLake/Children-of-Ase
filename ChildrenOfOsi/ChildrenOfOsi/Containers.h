#pragma once

#include "common.h"
#include "Texture.h"

class Hero;
class Soldier;
class SplSoldier;
class LivingObj;
class WorldObj;
class NPC;
class Attack;

class Containers
{
public:

	static std::unordered_map<std::string, Hero*> hero_table;
	static std::unordered_map<std::string, LivingObj*> livingObj_table;
	static std::unordered_map<std::string, Attack*> Attack_table;
	static std::unordered_map<std::string, Soldier*> soldier_table;
	static std::unordered_map<std::string, SplSoldier*> spl_soldier_table;
	static std::unordered_map<std::string, WorldObj*> worldObj_table;
	static std::unordered_map<std::string, NPC*> npc_table;
	static std::unordered_map<std::string, Texture*> texture_table;

	Containers();
	~Containers();

	static void add_hero(std::string, Hero*);
	static void add_livingObj(std::string, LivingObj*);
	static void add_Attack(std::string, Attack*);
	static void add_soldier(std::string, Soldier*);
	static void add_spl_soldier(std::string, SplSoldier*);
	static void add_worldObj(std::string, WorldObj*);
	static void add_npc(std::string, NPC*);
	static void add_texture(std::string, Texture*);
};
