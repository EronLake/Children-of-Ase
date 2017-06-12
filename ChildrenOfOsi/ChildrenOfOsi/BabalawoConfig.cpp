#include "stdafx.h"
#include "BabalawoConfig.h"


BabalawoConfig::BabalawoConfig()
{
}


BabalawoConfig::~BabalawoConfig()
{
}

void BabalawoConfig::import_config(vector<WorldObj*>* recVec_ptr, unordered_map<Texture*, pair<string, int>>* textureMap, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{
	bool alive = true;
	Json::Value root;
	while (alive) {

		Json::Reader reader;
		Json::CharReaderBuilder builder;
		//std::string test = 
		std::ifstream test("../ChildrenofOsi/babalawo_config.json", std::ifstream::binary);
		std::string errs;
		bool ok = reader.parse(test, root, false);
		if (!ok)
		{
			// report to the user the failure and their locations in the document.
			std::cout << errs.c_str() << "\n";
		}

		std::string encoding = root.get("encoding", "UTF-8").asString();
		std::cout << encoding << "\n";
		alive = false;
		test.close();
	}

	for (auto itr = root.begin(); itr != root.end(); itr++)
	{
		set_babalawo(recVec_ptr, gameplay_func, tBuffer, (*itr)["x"].asFloat(), (*itr)["y"].asFloat(),
			(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
			(*itr)["name"].asString(),
			(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
			(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat(),
			(*itr)["health"].asInt());

		//set sprites for soldiers
		init_sprites(gameplay_func, tBuffer, textureMap, itr, (*itr)["name"].asString());
	}
}

void BabalawoConfig::set_babalawo(vector<WorldObj*>* recVec_ptr, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width,
	float hight, std::string name, float bodyx1, float bodyx2, float bodyy1, float bodyy2, int health)
{
	if (!Containers::npc_table[name]) {
		gameplay_func->add_npc(name, 100 * x, 100 * y, true);
		tBuffer->run();

		Containers::npc_table[name]->setWidth(width);
		Containers::npc_table[name]->setHeight(hight);
		Containers::npc_table[name]->offsetBody(0, bodyx1, bodyx2, bodyy1, bodyy2);
		Containers::npc_table[name]->offset_effect(0, 100, 100, 100, 100);

		Containers::npc_table[name]->setName(name);

		Containers::npc_table[name]->setInteractable(true);

		Containers::npc_table[name]->setHealth(health);

		Containers::npc_table[name]->set_npc_type(2);
	}

	

	//push to recVec
	recVec_ptr->push_back(Containers::npc_table[name]);
}


void BabalawoConfig::init_sprites(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, unordered_map<Texture*,
	pair<string, int>>*textureMap, Json::Value::iterator itr, std::string name)
{

	//these sprites all soldiers have
	auto sprites = (*itr)["sprites"];

	//sets the oppropreate reagion config so that load by region works properly
	std::set<Texture*>* region_con;

	std::string path;

	//if statements check to see if the given soldier name(without the number) is in the name

	if (name.find("Oasis_Babalawo") != string::npos)
	{
		region_con = &ObjConfig::oasis_con;
		//path = SOLDIER_OASIS_PATH;
	}
	else if (name.find("Jungle_Babalawo") != string::npos)
	{
		region_con = &ObjConfig::jungle_con;
		//path = SOLDIER_JUNGLE_PATH;
	}
	else if (name.find("Mountain_Babalawo") != string::npos)
	{
		region_con = &ObjConfig::mountain_con;
		//path = SOLDIER_MOUNTAIN_PATH;
	}
	else //if ogun soldier
	{
		region_con = &ObjConfig::marsh_con;
		//path = SOLDIER_OGUN_PATH;
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
		(*textureMap)[Containers::texture_table[itor["0"].asString()]] = pair<string, int>(SPRITES_PATH + itor["0"].asString() + ".png", itor["1"].asInt()/*frame_num*/);
		//push to appropreate region config
		region_con->insert(Containers::texture_table[itor["0"].asString()]);
	}


	//set the texture to the appropriate sprite 
	Containers::npc_table[name]->sprite.setTexture(Containers::texture_table[sprites["setTexture"]["0"].asString()]);
	Containers::npc_table[name]->sprite.setIdleTexture(Containers::texture_table[sprites["setIdleTexture"]["0"].asString()]);

	Containers::npc_table[name]->sprite.id_up = Containers::texture_table[sprites["id_up"]["0"].asString()];
	Containers::npc_table[name]->sprite.id_left = Containers::texture_table[sprites["id_left"]["0"].asString()];
	Containers::npc_table[name]->sprite.id_right = Containers::texture_table[sprites["id_right"]["0"].asString()];
	Containers::npc_table[name]->sprite.id_down = Containers::texture_table[sprites["id_down"]["0"].asString()];

	//Containers::soldier_table[name]->sprite.up = Containers::texture_table[sprites["walk_up"]["0"].asString()];
	//Containers::soldier_table[name]->sprite.down = Containers::texture_table[sprites["walk_down"]["0"].asString()];
	//Containers::soldier_table[name]->sprite.left = Containers::texture_table[sprites["walk_left"]["0"].asString()];
	//Containers::soldier_table[name]->sprite.right = Containers::texture_table[sprites["walk_right"]["0"].asString()];

	/*Containers::npc_table[name]->sprite.up = Containers::texture_table[sprites["sprint_up"]["0"].asString()];
	Containers::npc_table[name]->sprite.down = Containers::texture_table[sprites["sprint_down"]["0"].asString()];
	Containers::npc_table[name]->sprite.left = Containers::texture_table[sprites["sprint_left"]["0"].asString()];
	Containers::npc_table[name]->sprite.right = Containers::texture_table[sprites["sprint_right"]["0"].asString()];

	Containers::npc_table[name]->sprite.atk_up = Containers::texture_table[sprites["atk_up"]["0"].asString()];
	Containers::npc_table[name]->sprite.atk_down = Containers::texture_table[sprites["atk_down"]["0"].asString()];
	Containers::npc_table[name]->sprite.atk_left = Containers::texture_table[sprites["atk_left"]["0"].asString()];
	Containers::npc_table[name]->sprite.atk_right = Containers::texture_table[sprites["atk_right"]["0"].asString()];

	Containers::npc_table[name]->sprite.atk2_up = Containers::texture_table[sprites["atk2_up"]["0"].asString()];
	Containers::npc_table[name]->sprite.atk2_down = Containers::texture_table[sprites["atk2_down"]["0"].asString()];
	Containers::npc_table[name]->sprite.atk2_left = Containers::texture_table[sprites["atk2_left"]["0"].asString()];
	Containers::npc_table[name]->sprite.atk2_right = Containers::texture_table[sprites["atk2_right"]["0"].asString()];

	Containers::npc_table[name]->sprite.spin_up = Containers::texture_table[sprites["spin_up"]["0"].asString()];
	Containers::npc_table[name]->sprite.spin_down = Containers::texture_table[sprites["spin_down"]["0"].asString()];
	Containers::npc_table[name]->sprite.spin_left = Containers::texture_table[sprites["spin_left"]["0"].asString()];
	Containers::npc_table[name]->sprite.spin_right = Containers::texture_table[sprites["spin_right"]["0"].asString()];

	Containers::npc_table[name]->sprite.breathe_up = Containers::texture_table[sprites["breathe_up"]["0"].asString()];
	Containers::npc_table[name]->sprite.breathe_down = Containers::texture_table[sprites["breathe_down"]["0"].asString()];
	Containers::npc_table[name]->sprite.breathe_left = Containers::texture_table[sprites["breathe_left"]["0"].asString()];
	Containers::npc_table[name]->sprite.breathe_right = Containers::texture_table[sprites["breathe_right"]["0"].asString()];

	Containers::npc_table[name]->sprite.hurt_up = Containers::texture_table[sprites["hurt_up"]["0"].asString()];
	Containers::npc_table[name]->sprite.hurt_down = Containers::texture_table[sprites["hurt_down"]["0"].asString()];
	Containers::npc_table[name]->sprite.hurt_left = Containers::texture_table[sprites["hurt_left"]["0"].asString()];
	Containers::npc_table[name]->sprite.hurt_right = Containers::texture_table[sprites["hurt_right"]["0"].asString()];

	Containers::npc_table[name]->sprite.death_up = Containers::texture_table[sprites["death_up"]["0"].asString()];
	Containers::npc_table[name]->sprite.death_down = Containers::texture_table[sprites["death_down"]["0"].asString()];
	Containers::npc_table[name]->sprite.death_left = Containers::texture_table[sprites["death_left"]["0"].asString()];
	Containers::npc_table[name]->sprite.death_right = Containers::texture_table[sprites["death_right"]["0"].asString()];*/
}

