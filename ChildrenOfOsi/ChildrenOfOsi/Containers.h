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
class Memory;
class Action;
class Tag;
class ConversationPoint;

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

	static std::unordered_map<std::string, Memory*> oya_memory_table;
	static std::unordered_map<std::string, Memory*> yemoja_memory_table;
	static std::unordered_map<std::string, Memory*> oshosi_memory_table;
	static std::unordered_map<std::string, Memory*> ogun_memory_table;
	static std::unordered_map<std::string, Memory*> shango_memory_table;

	static std::unordered_map<std::string, Action*> action_table;

	static std::unordered_map<std::string, Tag*> tag_table;
	static std::unordered_map<std::string, ConversationPoint*> conv_point_table;

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
	static void add_memory(std::string, int hero_name, Memory*);
	static void add_action(std::string, Action*);
	static void add_tag(std::string, Tag*);
	static void add_conv_point(std::string, ConversationPoint*);
};
