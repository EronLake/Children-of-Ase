#include "stdafx.h"
#include "SoldierConfig.h"


SoldierConfig::SoldierConfig()
{
}


SoldierConfig::~SoldierConfig()
{
}

void SoldierConfig::import_config(vector<WorldObj*>* movVec, unordered_map<Texture*, pair<string, int>>* textureMap, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{
	Json::Value root;
	Json::Reader reader;


	std::ifstream file("soldier_config.json");

	file >> root;

	for (auto itr = root.begin(); itr != root.end(); itr++)
	{
		for (int sol_num = 0; sol_num < (*itr)["soldier_number"].asInt(); sol_num++) {
			//creates a soldier name with the number attached at the end
			std::string soldier_name = (*itr)["name"].asString() + "_" + std::to_string(sol_num);

			set_soldier(movVec, gameplay_func, tBuffer, (*itr)["x"].asFloat() + (sol_num+1) * 2, (*itr)["y"].asFloat(),
				(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
				soldier_name, 
				(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
				(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat(),
				(*itr)["health"].asInt(), (*itr)["max_stamina"].asInt(),
				sol_num);

			//set sprites for soldiers
			init_sprites(gameplay_func, tBuffer, textureMap, itr, soldier_name, sol_num);
		}
	}

	for (auto itr = root.begin(); itr != root.end(); itr++)
	{
		for (int sol_num = 0; sol_num < (*itr)["soldier_number"].asInt(); sol_num++) {
			//creates a soldier name with the number attached at the end
			std::string soldier_name = (*itr)["name"].asString() + "_" + std::to_string(sol_num);

			init_attacks(gameplay_func, tBuffer, textureMap, itr, soldier_name, sol_num);
		}
	}
}

void SoldierConfig::set_soldier(vector<WorldObj*>* movVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width,
	float hight, std::string name, float bodyx1, float bodyx2, float bodyy1, float bodyy2, int health, int max_stamina
	,int sol_num)
{

	gameplay_func->add_soldier(name, 100 * x, 100 * y, true);

	tBuffer->run();

	Containers::soldier_table[name]->setName(name);
	Containers::soldier_table[name]->setWidth(width);
	Containers::soldier_table[name]->setHeight(hight);
	Containers::soldier_table[name]->offsetBody(0, bodyx1, bodyx2, bodyy1, bodyy2);
	Containers::soldier_table[name]->offset_effect(0, 100, 100, 100, 100);

	Containers::soldier_table[name]->setInteractable(true);

	Containers::soldier_table[name]->setHealth(health);
	Containers::soldier_table[name]->setMaxStamina(max_stamina);

	//Containers::npc_table[name]->set_npc_type(0);

	//push to moveVec
	movVec->push_back(Containers::soldier_table[name]);
}


void SoldierConfig::init_sprites(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, unordered_map<Texture*, 
							pair<string, int>>* textureMap, Json::Value::iterator itr, std::string name, int sol_num)
{

	//these sprites all soldiers have
	auto sprites = (*itr)["sprites"];

	//sets the oppropreate reagion config so that load by region works properly
	std::set<Texture*>* region_con;

	std::string path;

	//if statements check to see if the given soldier name(without the number) is in the name

	if (name.find("Oasis_Soldier") != string::npos)
	{
		region_con = &ObjConfig::oasis_con;
		path = SOLDIER_OASIS_PATH;
	}
	else if (name.find("Jungle_Soldier") != string::npos)
	{
		region_con = &ObjConfig::jungle_con;
		path = SOLDIER_JUNGLE_PATH;
	}
	else if (name.find("Mountain_Soldier") != string::npos)
	{
		region_con = &ObjConfig::mountain_con;
		path = SOLDIER_MOUNTAIN_PATH;
	}
	else if (name.find("Ogun_Soldier") != string::npos) //if ogun soldier
	{
		region_con = &ObjConfig::marsh_con;
		path = SOLDIER_OGUN_PATH;
	}
	else //if (name.find("Shango_Soldier") != string::npos)
	{
		region_con = &ObjConfig::oasis_con;
		path = SOLDIER_OGUN_PATH; 
	}


	for (auto itor : sprites)
	{
		//checks if the texture is already loaded
		if (!Containers::texture_table[itor["0"].asString()])
		{
			//create textures for the soldiers 
			gameplay_func->add_texture(itor["0"].asString(), 0, 0, 0);
		}
	}

	tBuffer->run();
	for (auto itor : sprites)
	{
		//create textures for the soldiers 
		(*textureMap)[Containers::texture_table[itor["0"].asString()]] = pair<string, int>(path + itor["0"].asString() + ".png", itor["1"].asInt()/*frame_num*/);
		//push to appropreate region config
		region_con->insert(Containers::texture_table[itor["0"].asString()]);
	}


	//set the texture to the appropriate sprite 
	Containers::soldier_table[name]->sprite.setTexture(Containers::texture_table[sprites["setTexture"]["0"].asString()]);
	Containers::soldier_table[name]->sprite.setIdleTexture(Containers::texture_table[sprites["setIdleTexture"]["0"].asString()]);

	Containers::soldier_table[name]->sprite.id_up = Containers::texture_table[sprites["id_up"]["0"].asString()];
	Containers::soldier_table[name]->sprite.id_left = Containers::texture_table[sprites["id_left"]["0"].asString()];
	Containers::soldier_table[name]->sprite.id_right = Containers::texture_table[sprites["id_right"]["0"].asString()];
	Containers::soldier_table[name]->sprite.id_down = Containers::texture_table[sprites["id_down"]["0"].asString()];

	//Containers::soldier_table[name]->sprite.up = Containers::texture_table[sprites["walk_up"]["0"].asString()];
	//Containers::soldier_table[name]->sprite.down = Containers::texture_table[sprites["walk_down"]["0"].asString()];
	//Containers::soldier_table[name]->sprite.left = Containers::texture_table[sprites["walk_left"]["0"].asString()];
	//Containers::soldier_table[name]->sprite.right = Containers::texture_table[sprites["walk_right"]["0"].asString()];

	Containers::soldier_table[name]->sprite.up = Containers::texture_table[sprites["sprint_up"]["0"].asString()];
	Containers::soldier_table[name]->sprite.down = Containers::texture_table[sprites["sprint_down"]["0"].asString()];
	Containers::soldier_table[name]->sprite.left = Containers::texture_table[sprites["sprint_left"]["0"].asString()];
	Containers::soldier_table[name]->sprite.right = Containers::texture_table[sprites["sprint_right"]["0"].asString()];

	Containers::soldier_table[name]->sprite.atk_up = Containers::texture_table[sprites["atk_up"]["0"].asString()];
	Containers::soldier_table[name]->sprite.atk_down = Containers::texture_table[sprites["atk_down"]["0"].asString()];
	Containers::soldier_table[name]->sprite.atk_left = Containers::texture_table[sprites["atk_left"]["0"].asString()];
	Containers::soldier_table[name]->sprite.atk_right = Containers::texture_table[sprites["atk_right"]["0"].asString()];

	Containers::soldier_table[name]->sprite.atk2_up = Containers::texture_table[sprites["atk2_up"]["0"].asString()];
	Containers::soldier_table[name]->sprite.atk2_down = Containers::texture_table[sprites["atk2_down"]["0"].asString()];
	Containers::soldier_table[name]->sprite.atk2_left = Containers::texture_table[sprites["atk2_left"]["0"].asString()];
	Containers::soldier_table[name]->sprite.atk2_right = Containers::texture_table[sprites["atk2_right"]["0"].asString()];

	Containers::soldier_table[name]->sprite.spin_up = Containers::texture_table[sprites["spin_up"]["0"].asString()];
	Containers::soldier_table[name]->sprite.spin_down = Containers::texture_table[sprites["spin_down"]["0"].asString()];
	Containers::soldier_table[name]->sprite.spin_left = Containers::texture_table[sprites["spin_left"]["0"].asString()];
	Containers::soldier_table[name]->sprite.spin_right = Containers::texture_table[sprites["spin_right"]["0"].asString()];

	Containers::soldier_table[name]->sprite.breathe_up = Containers::texture_table[sprites["breathe_up"]["0"].asString()];
	Containers::soldier_table[name]->sprite.breathe_down = Containers::texture_table[sprites["breathe_down"]["0"].asString()];
	Containers::soldier_table[name]->sprite.breathe_left = Containers::texture_table[sprites["breathe_left"]["0"].asString()];
	Containers::soldier_table[name]->sprite.breathe_right = Containers::texture_table[sprites["breathe_right"]["0"].asString()];

	Containers::soldier_table[name]->sprite.hurt_up = Containers::texture_table[sprites["hurt_up"]["0"].asString()];
	Containers::soldier_table[name]->sprite.hurt_down = Containers::texture_table[sprites["hurt_down"]["0"].asString()];
	Containers::soldier_table[name]->sprite.hurt_left = Containers::texture_table[sprites["hurt_left"]["0"].asString()];
	Containers::soldier_table[name]->sprite.hurt_right = Containers::texture_table[sprites["hurt_right"]["0"].asString()];

	Containers::soldier_table[name]->sprite.death_up = Containers::texture_table[sprites["death_up"]["0"].asString()];
	Containers::soldier_table[name]->sprite.death_down = Containers::texture_table[sprites["death_down"]["0"].asString()];
	Containers::soldier_table[name]->sprite.death_left = Containers::texture_table[sprites["death_left"]["0"].asString()];
	Containers::soldier_table[name]->sprite.death_right = Containers::texture_table[sprites["death_right"]["0"].asString()];
}

void SoldierConfig::init_attacks(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, unordered_map<Texture*, 
						pair<string, int>>* textureMap, Json::Value::iterator itr, std::string name, int sol_num)
{

	//retrieves attacks from json
	auto attacks = (*itr)["attacks"];

	Soldier* cur_soldier;

	//sets the oppropreate reagion config so that load by region works properly
	std::set<Texture*>* region_con;

	std::string path;

	//if statements check to see if the given soldier name(without the number) is in the name

	if (name.find("Oasis_Soldier") != string::npos)
	{
		region_con = &ObjConfig::oasis_con;
		path = SOLDIER_OASIS_PATH;
	}
	else if (name.find("Jungle_Soldier") != string::npos)
	{
		region_con = &ObjConfig::jungle_con;
		path = SOLDIER_JUNGLE_PATH;
	}
	else if (name.find("Mountain_Soldier") != string::npos)
	{
		region_con = &ObjConfig::mountain_con;
		path = SOLDIER_MOUNTAIN_PATH;
	}
	else //if ogun soldier
	{
		region_con = &ObjConfig::marsh_con;
		path = SOLDIER_OGUN_PATH;
	}

	cur_soldier = Containers::soldier_table[name];

	for (auto itor : attacks["sprites"])
	{
		//checks if the texture is already loaded
		if (!Containers::texture_table[itor["0"].asString()])
		{
			//create textures for the soldiers 
			gameplay_func->add_texture(itor["0"].asString(), 0, 0, 0);
		}
	}

	tBuffer->run();

	for (auto itor : attacks["sprites"])
	{
		//create textures for the soldiers
		(*textureMap)[Containers::texture_table[itor["0"].asString()]] = pair<string, int>("Assets/Sprites/" + itor["0"].asString() + ".png", itor["1"].asInt()/*frame_num*/);
		//push to appropreate region config
		region_con->insert(Containers::texture_table[itor["0"].asString()]);
	}

	//initialize melee attack
	gameplay_func->add_Attack("melee_" + cur_soldier->getKey(), cur_soldier->body[0].getX(), cur_soldier->body[0].getY(), true, 10);
	tBuffer->run();

	cur_soldier->melee = Containers::Attack_table["melee_" + cur_soldier->getKey()];

	cur_soldier->melee->set_name((*itr)["melee"]["set_name"].asInt());
	cur_soldier->melee->setDmg((*itr)["melee"]["set_dmg"].asInt());
	cur_soldier->melee->setSpeed((*itr)["melee"]["set_speed"].asInt());
	cur_soldier->melee->setBaseDir((*itr)["melee"]["set_base_dir"].asInt());
	cur_soldier->melee->setCoolDown((*itr)["melee"]["set_cool_down"].asInt());//35
	cur_soldier->melee->setStaminaCost((*itr)["melee"]["set_stamina_cost"].asInt());
	cur_soldier->melee->setPause((*itr)["melee"]["set_pause"].asInt());
	cur_soldier->melee->setDestroy((*itr)["melee"]["set_destroy"].asBool());
	cur_soldier->melee->setKeep((*itr)["melee"]["set_Keep"].asBool());
	cur_soldier->melee->setWidth(cur_soldier->body[0].getWidth());
	cur_soldier->melee->setHeight(cur_soldier->body[0].getHeight());
	cur_soldier->set_creator_of_melee();

	//NEED TO IMPORT GLOBAL TEXTURES
	cur_soldier->melee->sprite.setTexture(Containers::texture_table["border"]);


	//initialize the rest of the attacks

	tBuffer->run();
	for (auto attack = attacks.begin(); attack != attacks.end(); attack++)
	{
		std::vector<Attack*> attack_vec;

		for (auto itor = (*attack).begin(); itor != (*attack).end(); itor++)
		{
			for (auto itr2 : (*itor)["sprites"])
			{
				//checks if the texture is already loaded
				if (!Containers::texture_table[itr2["0"].asString()])
				{
					//create textures for the soldiers 
					gameplay_func->add_texture(itr2["0"].asString(), 0, 0, 0);
				}
			}
			tBuffer->run();

			for (auto itr2 : (*itor)["sprites"])
			{
				//create textures for the soldiers
				(*textureMap)[Containers::texture_table[itr2["0"].asString()]] = pair<string, int>("Assets/Sprites/" + itr2["0"].asString() + ".png", itr2["1"].asInt()/*frame_num*/);
				//push to appropreate region config
				region_con->insert(Containers::texture_table[itr2["0"].asString()]);
			}

			Attack* new_attack = new Attack();
			attack_vec.push_back(new_attack);

			new_attack->set_name((*itor)["set_name"].asInt());
			new_attack->setDmg((*itor)["set_dmg"].asInt());
			new_attack->setSpeed((*itor)["set_speed"].asInt());
			new_attack->setBaseDir((*itor)["set_base_dir"].asInt());
			new_attack->setCoolDown((*itor)["set_cool_down"].asInt());//35
			new_attack->setStaminaCost((*itor)["set_stamina_cost"].asInt());
			new_attack->setPause((*itor)["set_pause"].asInt());
			new_attack->setDestroy((*itor)["set_destroy"].asBool());
			new_attack->setKeep((*itor)["set_Keep"].asBool());
			new_attack->setWidth(cur_soldier->body[0].getWidth());
			new_attack->setHeight(cur_soldier->body[0].getHeight());
			new_attack->setDuration((*itor)["set_duration"].asInt());
			new_attack->setAseCost((*itor)["set_ase_cost"].asInt());
			new_attack->setCanCancel((*itor)["set_can_cancel"].asBool());
			new_attack->setTurn((*itor)["set_turn"].asBool());

			//set the texture to the appropriate sprite 
			new_attack->sprite.up = Containers::texture_table[(*itor)["sprites"]["up"]["0"].asString()];
			new_attack->sprite.left = Containers::texture_table[(*itor)["sprites"]["left"]["0"].asString()];
			new_attack->sprite.right = Containers::texture_table[(*itor)["sprites"]["right"]["0"].asString()];
			new_attack->sprite.down = Containers::texture_table[(*itor)["sprites"]["down"]["0"].asString()];

			new_attack->sprite.setTexture(Containers::texture_table["border"]);
			new_attack->set_creator(cur_soldier);

			cur_soldier->addAttackType(new_attack);
		}
		for (int i = 0; i < attack_vec.size(); i++)
		{
			if (i + 1 < attack_vec.size())
			{
				attack_vec[i]->setNextAttack(attack_vec[i + 1]);
			}
		}
	}
}
