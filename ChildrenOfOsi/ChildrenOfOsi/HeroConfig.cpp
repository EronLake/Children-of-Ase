#include "stdafx.h"
#include "HeroConfig.h"


HeroConfig::HeroConfig()
{
}


HeroConfig::~HeroConfig()
{
}

void HeroConfig::import_config(vector<WorldObj*>* movVec, unordered_map<Texture*, pair<string, int>>* textureMap, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{
	Json::Value root;
	Json::Reader reader;


	std::ifstream file("hero_config.json");

	file >> root;

	for (auto itr = root.begin(); itr != root.end(); itr++)
	{
		set_hero(movVec, gameplay_func, tBuffer, (*itr)["x"].asFloat(), (*itr)["y"].asFloat(),
			(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
			(*itr)["name"].asString(), (*itr)["hero_id"].asInt(),
			(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
			(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat(),
			(*itr)["health"].asInt(), (*itr)["max_stamina"].asInt(),
			(*itr)["aggression"].asInt(), (*itr)["kindness"].asInt(), (*itr)["honor"].asInt(),
			(*itr)["pride"].asInt(), (*itr)["recklessness"].asInt(), (*itr)["extroversion"].asInt(),
			(*itr)["greed"].asInt());

		//set sprites for heroes
		init_sprites(gameplay_func,tBuffer, textureMap, itr, (*itr)["name"].asString(),(*itr)["hero_id"].asInt());

	}

	for (auto itr = root.begin(); itr != root.end(); itr++)
	{
		init_hero_planner(gameplay_func, tBuffer, (*itr)["name"].asString(), (*itr)["hero_id"].asInt());
	}

	AIController::init_plans();

}

void HeroConfig::set_hero(vector<WorldObj*>* movVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width,
	float hight, std::string name, int hero_id, float bodyx1, float bodyx2, float bodyy1, float bodyy2, int health, int max_stamina,
	int a, int k, int h, int p, int r, int e, int g)
{

	gameplay_func->add_hero(name, 100 * x, 100 * y, true);

	tBuffer->run();

	if (hero_id == SHANGO)
	{
		dynamic_cast<Player*>(Containers::hero_table[name])->setTalkDist(20);
	}

	Containers::hero_table[name]->name = hero_id;
	Containers::hero_table[name]->setName(name);
	Containers::hero_table[name]->setWidth(width);
	Containers::hero_table[name]->setHeight(hight);
	Containers::hero_table[name]->offsetBody(0, bodyx1, bodyx2, bodyy1, bodyy2);

	//needs to be handled separately
	//Containers::hero_table[name]->sprite.setTexture(Containers::texture_table[tex_file]);

	Containers::hero_table[name]->setInteractable(true);
	Containers::hero_table[name]->setPersonality(a, k, h, p, r, e, g);

	Containers::hero_table[name]->setHealth(health);
	Containers::hero_table[name]->setMaxStamina(max_stamina);

	//push to moveVec
	movVec->push_back(Containers::hero_table[name]);
}


void HeroConfig::init_sprites(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, unordered_map<Texture*, pair<string, int>>* textureMap, Json::Value::iterator itr, std::string name, int hero_id)
{

	//these sprites all heroes have
	auto sprites = (*itr)["sprites"];

	//sets the oppropreate reagion config so that load by region works properly
	vector<Texture*>* region_con;

	if (hero_id == SHANGO)
	{
		region_con = &ObjConfig::standard_con;
	}
	else if (hero_id == YEMOJA)
	{
		region_con = &ObjConfig::oasis_con;
	}
	else if (hero_id == OYA)
	{
		region_con = &ObjConfig::jungle_con;
	}
	else if (hero_id == OSHOSI)
	{
		region_con = &ObjConfig::mountain_con;
	}
	else //if (hero_id == OGUN)
	{
		region_con = &ObjConfig::marsh_con;
	}
	

	for (auto itor : sprites)
	{
		//create textures for the heroes 

		//checks if the texture is already loaded
		if (!Containers::texture_table[itor["0"].asString()]) 
		{
			gameplay_func->add_texture(itor["0"].asString(), 0, 0, 0);
		}
	}

	tBuffer->run();
	for (auto itor : sprites)
	{
		//create textures for the heroes 
		(*textureMap)[Containers::texture_table[itor["0"].asString()]] = pair<string, int>("Assets/Sprites/" + itor["0"].asString() + ".png", itor["1"].asInt()/*frame_num*/);
		//push to appropreate region config
		region_con->push_back(Containers::texture_table[itor["0"].asString()]);
	}


	//set the texture to the appropriate sprite 
	Containers::hero_table[name]->sprite.setTexture(Containers::texture_table[sprites["setTexture"]["0"].asString()]);
	Containers::hero_table[name]->sprite.setIdleTexture(Containers::texture_table[sprites["setIdleTexture"]["0"].asString()]);

	Containers::hero_table[name]->sprite.up = Containers::texture_table[sprites["up"]["0"].asString()];
	Containers::hero_table[name]->sprite.down = Containers::texture_table[sprites["down"]["0"].asString()];
	Containers::hero_table[name]->sprite.left = Containers::texture_table[sprites["left"]["0"].asString()];
	Containers::hero_table[name]->sprite.right = Containers::texture_table[sprites["right"]["0"].asString()];

	Containers::hero_table[name]->sprite.id_up = Containers::texture_table[sprites["id_up"]["0"].asString()];
	Containers::hero_table[name]->sprite.id_left = Containers::texture_table[sprites["id_left"]["0"].asString()];
	Containers::hero_table[name]->sprite.id_right = Containers::texture_table[sprites["id_right"]["0"].asString()];
	Containers::hero_table[name]->sprite.id_down = Containers::texture_table[sprites["id_down"]["0"].asString()];

	Containers::hero_table[name]->sprite.atk_up = Containers::texture_table[sprites["atk_up"]["0"].asString()];
	Containers::hero_table[name]->sprite.atk_down = Containers::texture_table[sprites["atk_down"]["0"].asString()];
	Containers::hero_table[name]->sprite.atk_left = Containers::texture_table[sprites["atk_left"]["0"].asString()];
	Containers::hero_table[name]->sprite.atk_right = Containers::texture_table[sprites["atk_right"]["0"].asString()];

	Containers::hero_table[name]->sprite.atk2_up = Containers::texture_table[sprites["atk2_up"]["0"].asString()];
	Containers::hero_table[name]->sprite.atk2_down = Containers::texture_table[sprites["atk2_down"]["0"].asString()];
	Containers::hero_table[name]->sprite.atk2_left = Containers::texture_table[sprites["atk2_left"]["0"].asString()];
	Containers::hero_table[name]->sprite.atk2_right = Containers::texture_table[sprites["atk2_right"]["0"].asString()];

	Containers::hero_table[name]->sprite.spin_up = Containers::texture_table[sprites["spin_up"]["0"].asString()];
	Containers::hero_table[name]->sprite.spin_down = Containers::texture_table[sprites["spin_down"]["0"].asString()];
	Containers::hero_table[name]->sprite.spin_left = Containers::texture_table[sprites["spin_left"]["0"].asString()];
	Containers::hero_table[name]->sprite.spin_right = Containers::texture_table[sprites["spin_right"]["0"].asString()];

	Containers::hero_table[name]->sprite.breathe_up = Containers::texture_table[sprites["breathe_up"]["0"].asString()];
	Containers::hero_table[name]->sprite.breathe_down = Containers::texture_table[sprites["breathe_down"]["0"].asString()];
	Containers::hero_table[name]->sprite.breathe_left = Containers::texture_table[sprites["breathe_left"]["0"].asString()];
	Containers::hero_table[name]->sprite.breathe_right = Containers::texture_table[sprites["breathe_right"]["0"].asString()];

	Containers::hero_table[name]->sprite.hurt_up = Containers::texture_table[sprites["hurt_up"]["0"].asString()];
	Containers::hero_table[name]->sprite.hurt_down = Containers::texture_table[sprites["hurt_down"]["0"].asString()];
	Containers::hero_table[name]->sprite.hurt_left = Containers::texture_table[sprites["hurt_left"]["0"].asString()];
	Containers::hero_table[name]->sprite.hurt_right = Containers::texture_table[sprites["hurt_right"]["0"].asString()];

	Containers::hero_table[name]->sprite.death_up = Containers::texture_table[sprites["death_up"]["0"].asString()];
	Containers::hero_table[name]->sprite.death_down = Containers::texture_table[sprites["death_down"]["0"].asString()];
	Containers::hero_table[name]->sprite.death_left = Containers::texture_table[sprites["death_left"]["0"].asString()];
	Containers::hero_table[name]->sprite.death_right = Containers::texture_table[sprites["death_right"]["0"].asString()];
}




void HeroConfig::init_hero_planner(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string name, int hero_id)
{
	//initializes action pool for given hero
	ActionConfig::import_config(gameplay_func, tBuffer, Containers::hero_table[name]);

	//initializes planner for given hero
	Planner* heroPlanner = new Planner(Containers::hero_table[name]);
	AIController::set_plan(hero_id, heroPlanner);
}



void HeroConfig::set_hero_sprites()
{

	Json::Value root;
	Json::Reader reader;

	std::ifstream file("hero_config.json");

	file >> root;

	for (auto itr = root.begin(); itr != root.end(); itr++)
	{
		auto sprites = (*itr)["sprites"];

		for (auto itor : sprites)
		{
			Containers::hero_table[(*itr)["name"].asString()]->sprite.setTexture(Containers::texture_table[itor["0"].asString()]);
		}
	}
}
