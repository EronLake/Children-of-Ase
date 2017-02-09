#pragma once

#include "common.h"
#include "Hero.h"
#include "SplSoldier.h"
#include "LivingObj.h"
#include "WorldObj.h"
#include "NPC.h"
#include "Projectile.h"
#include "Texture.h"

class Containers
{
public:

	static std::unordered_map<std::string, Hero*> hero_table;
	static std::unordered_map<std::string, LivingObj*> livingObj_table;
	static std::unordered_map<std::string, Projectile*> projectile_table;
	static std::unordered_map<std::string, Soldier*> soldier_table;
	static std::unordered_map<std::string, SplSoldier*> spl_soldier_table;
	static std::unordered_map<std::string, WorldObj*> worldObj_table;
	static std::unordered_map<std::string, NPC*> npc_table;

	//still need to impliment store function
	static std::unordered_map<std::string, Texture*> texture_table;

	Containers();
	~Containers();

	static void add_hero(std::string, Hero*);
	static void add_livingObj(std::string, LivingObj*);
	static void add_projectile(std::string, Projectile*);
	static void add_soldier(std::string, Soldier*);
	static void add_spl_soldier(std::string, SplSoldier*);
	static void add_worldObj(std::string, WorldObj*);
	static void add_npc(std::string, NPC*);

	//still need to impliment store function
	static void add_texture(std::string, Texture*);
};
