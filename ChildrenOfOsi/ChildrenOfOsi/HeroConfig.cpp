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
		init_attacks(gameplay_func, tBuffer, textureMap, itr, (*itr)["name"].asString(), (*itr)["hero_id"].asInt());
	}

}

void HeroConfig::set_hero(vector<WorldObj*>* movVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width,
	float hight, std::string name, int hero_id, float bodyx1, float bodyx2, float bodyy1, float bodyy2, int health, int max_stamina,
	int a, int k, int h, int p, int r, int e, int g)
{
	bool pre_loaded = true;
	if (!Containers::hero_table[name]) {
		gameplay_func->add_hero(name, 100 * x, 100 * y, true);

		tBuffer->run();

		Containers::hero_table[name]->name = hero_id;
		Containers::hero_table[name]->setName(name);
		Containers::hero_table[name]->setWidth(width);
		Containers::hero_table[name]->setHeight(hight);
		Containers::hero_table[name]->offsetBody(0, bodyx1, bodyx2, bodyy1, bodyy2);
		Containers::hero_table[name]->offset_effect(0, 100, 100, 100, 100);

		//needs to be handled separately
		//Containers::hero_table[name]->sprite.setTexture(Containers::texture_table[tex_file]);

		Containers::hero_table[name]->setInteractable(true);
		Containers::hero_table[name]->setPersonality(a, k, h, p, r, e, g);

		Containers::hero_table[name]->setHealth(health);
		Containers::hero_table[name]->setMaxStamina(max_stamina);

		//Containers::npc_table[name]->set_npc_type(0);
	}
	else
	{
		Containers::hero_table[name]->setX(x * 100);
		Containers::hero_table[name]->setY(y * 100);
		Containers::hero_table[name]->offset_effect(0, 100, 100, 100, 100);

		for (int i = 1; i < 6; i++) {
			if (i != hero_id) {
				Containers::hero_table[name]->rel[i]->setAffinity(50);
				Containers::hero_table[name]->rel[i]->setNotoriety(50);
				Containers::hero_table[name]->rel[i]->setStrength(50);
				Containers::hero_table[name]->rel[i]->setAffEstimate(50);
				Containers::hero_table[name]->rel[i]->setNotorEstimate(50);
				Containers::hero_table[name]->rel[i]->setStrEstimate(50);

				Containers::hero_table[name]->rel[i]->setChanged(0);

				//aff_counter = 0;
				//aff_max_change = 10;
				//not_counter = 0;
				//not_max_change = 10;
				//str_counter = 0;
				//str_max_change = 10;
			}

		}
		
	}

	if (hero_id == SHANGO)
	{
		Player* player = dynamic_cast<Player*>(Containers::hero_table[name]);
		player->setTalkDist(20);
		DialogueController::setPlayer(player);
	}


	//push to moveVec
	movVec->push_back(Containers::hero_table[name]);
}


void HeroConfig::init_sprites(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, unordered_map<Texture*, pair<string, int>>* textureMap, Json::Value::iterator itr, std::string name, int hero_id)
{

	//these sprites all heroes have
	auto sprites = (*itr)["sprites"];

	//sets the oppropreate reagion config so that load by region works properly
	std::set<Texture*>* region_con;

	std::string path;

	if (hero_id == SHANGO)
	{
		region_con = &ObjConfig::standard_con;
		path = SHANGO_PATH;
	}
	else if (hero_id == YEMOJA)
	{
		region_con = &ObjConfig::oasis_con;
		path = YEMOJA_PATH;
	}
	else if (hero_id == OYA)
	{
		region_con = &ObjConfig::jungle_con;
		path = OYA_PATH;
	}
	else if (hero_id == OSHOSI)
	{
		region_con = &ObjConfig::mountain_con;
		path = OSHOSI_PATH;
	}
	else //if (hero_id == OGUN)
	{
		region_con = &ObjConfig::marsh_con;
		path = OGUN_PATH;
	}
	

	for (auto itor : sprites)
	{
		//checks if the texture is already loaded
		if (!Containers::texture_table[itor["0"].asString()]) 
		{
			//create textures for the heroes 
			gameplay_func->add_texture(itor["0"].asString(), 0, 0, 0);
		}
	}

	tBuffer->run();
	for (auto itor : sprites)
	{
		//create textures for the heroes 
		(*textureMap)[Containers::texture_table[itor["0"].asString()]] = pair<string, int>(path + itor["0"].asString() + ".png", itor["1"].asInt()/*frame_num*/);
		//push to appropreate region config
		region_con->insert(Containers::texture_table[itor["0"].asString()]);
	}


	//set the texture to the appropriate sprite 
	Containers::hero_table[name]->sprite.setTexture(Containers::texture_table[sprites["setTexture"]["0"].asString()]);
	Containers::hero_table[name]->sprite.setIdleTexture(Containers::texture_table[sprites["setIdleTexture"]["0"].asString()]);

	Containers::hero_table[name]->sprite.id_up = Containers::texture_table[sprites["id_up"]["0"].asString()];
	Containers::hero_table[name]->sprite.id_left = Containers::texture_table[sprites["id_left"]["0"].asString()];
	Containers::hero_table[name]->sprite.id_right = Containers::texture_table[sprites["id_right"]["0"].asString()];
	Containers::hero_table[name]->sprite.id_down = Containers::texture_table[sprites["id_down"]["0"].asString()];

	//Containers::hero_table[name]->sprite.up = Containers::texture_table[sprites["walk_up"]["0"].asString()];
	//Containers::hero_table[name]->sprite.down = Containers::texture_table[sprites["walk_down"]["0"].asString()];
	//Containers::hero_table[name]->sprite.left = Containers::texture_table[sprites["walk_left"]["0"].asString()];
	//Containers::hero_table[name]->sprite.right = Containers::texture_table[sprites["walk_right"]["0"].asString()];

	Containers::hero_table[name]->sprite.up = Containers::texture_table[sprites["sprint_up"]["0"].asString()];
	Containers::hero_table[name]->sprite.down = Containers::texture_table[sprites["sprint_down"]["0"].asString()];
	Containers::hero_table[name]->sprite.left = Containers::texture_table[sprites["sprint_left"]["0"].asString()];
	Containers::hero_table[name]->sprite.right = Containers::texture_table[sprites["sprint_right"]["0"].asString()];

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

void HeroConfig::init_attacks(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, unordered_map<Texture*, pair<string, int>>* textureMap, Json::Value::iterator itr, std::string name, int hero_id)
{

	//these sprites all heroes have
	auto attacks = (*itr)["attacks"];

	Hero* cur_hero;

	//sets the oppropreate reagion config so that load by region works properly
	std::set<Texture*>* region_con;

	std::string path;

	if (hero_id == SHANGO)
	{
		region_con = &ObjConfig::standard_con;
		path = SHANGO_PATH;
	}
	else if (hero_id == YEMOJA)
	{
		region_con = &ObjConfig::oasis_con;
		path = YEMOJA_PATH;
	}
	else if (hero_id == OYA)
	{
		region_con = &ObjConfig::jungle_con;
		path = OYA_PATH;
	}
	else if (hero_id == OSHOSI)
	{
		region_con = &ObjConfig::mountain_con;
		path = OSHOSI_PATH;
	}
	else //if (hero_id == OGUN)
	{
		region_con = &ObjConfig::marsh_con;
		path = OGUN_PATH;
	}

	/*
	if (hero_id == SHANGO)
	{
		cur_hero = dynamic_cast<Player*>(Containers::hero_table[name]);
	}
	else 
	{
		cur_hero = Containers::hero_table[name];
	}
	*/

	cur_hero = Containers::hero_table[name];

	for (auto itor : attacks["sprites"])
	{
		//checks if the texture is already loaded
		if (!Containers::texture_table[itor["0"].asString()])
		{
			//create textures for the heroes 
			gameplay_func->add_texture(itor["0"].asString(), 0, 0, 0);
		}
	}

	tBuffer->run();

	for (auto itor : attacks["sprites"])
	{
		//create textures for the heroes
		(*textureMap)[Containers::texture_table[itor["0"].asString()]] = pair<string, int>("Assets/Sprites/" + itor["0"].asString() + ".png", itor["1"].asInt()/*frame_num*/);
		//push to appropreate region config
		region_con->insert(Containers::texture_table[itor["0"].asString()]);
	}

	//initialize melee attack
	if (!Containers::Attack_table["melee_" + cur_hero->getKey()]) {
		gameplay_func->add_Attack("melee_" + cur_hero->getKey(), cur_hero->body[0].getX(), cur_hero->body[0].getY(), true, 10);
	}

	tBuffer->run();

	cur_hero->melee = Containers::Attack_table["melee_" + cur_hero->getKey()];

	cur_hero->melee->set_name((*itr)["melee"]["set_name"].asInt());
	cur_hero->melee->setDmg((*itr)["melee"]["set_dmg"].asInt());
	cur_hero->melee->setSpeed((*itr)["melee"]["set_speed"].asInt());
	cur_hero->melee->setBaseDir((*itr)["melee"]["set_base_dir"].asInt());
	cur_hero->melee->setCoolDown((*itr)["melee"]["set_cool_down"].asInt());//35
	cur_hero->melee->setStaminaCost((*itr)["melee"]["set_stamina_cost"].asInt());
	cur_hero->melee->setPause((*itr)["melee"]["set_pause"].asInt());
	cur_hero->melee->setDestroy((*itr)["melee"]["set_destroy"].asBool());
	cur_hero->melee->setKeep((*itr)["melee"]["set_Keep"].asBool());
	cur_hero->melee->setWidth(cur_hero->body[0].getWidth());
	cur_hero->melee->setHeight(cur_hero->body[0].getHeight());
	cur_hero->set_creator_of_melee();

	//NEED TO IMPORT GLOBAL TEXTURES
	cur_hero->melee->sprite.setTexture(Containers::texture_table["border"]);
																																						

	//initialize the rest of the attacks
	
 	tBuffer->run();
	for (auto attack = attacks.begin(); attack != attacks.end(); attack++)
	{
		std::vector<Attack*> attack_vec;

		for (auto itor = (*attack).begin(); itor != (*attack).end();itor++)
		{
			for (auto itr2 : (*itor)["sprites"])
			{
				//checks if the texture is already loaded
				if (!Containers::texture_table[itr2["0"].asString()])
				{
					//create textures for the heroes 
					gameplay_func->add_texture(itr2["0"].asString(), 0, 0, 0);
				}
			}
			tBuffer->run();

			for (auto itr2 : (*itor)["sprites"])
			{
				//checks if the texture is already loaded
				if (!Containers::texture_table[itr2["0"].asString()])
				{
					//create textures for the heroes
					(*textureMap)[Containers::texture_table[itr2["0"].asString()]] = pair<string, int>("Assets/Sprites/" + itr2["0"].asString() + ".png", itr2["1"].asInt()/*frame_num*/);
					//push to appropreate region config
					region_con->insert(Containers::texture_table[itr2["0"].asString()]);
				}
			}

			//gameplay_func->add_Attack(attack.key().asString() + "_" + itor.key().asString() + cur_hero->getKey(), cur_hero->body[0].getX(), cur_hero->body[0].getY(), true, 10);
			//tBuffer->run();

			//Attack* new_attack = Containers::Attack_table[attack.key().asString() + "_" + itor.key().asString() + cur_hero->getKey()];
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
			new_attack->setWidth(cur_hero->body[0].getWidth());
			new_attack->setHeight(cur_hero->body[0].getHeight());
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
			new_attack->set_creator(cur_hero);

			cur_hero->addAttackType(new_attack);
		}
		for (int i = 0; i < attack_vec.size(); i++) 
		{
			if (i + 1 < attack_vec.size())
			{
				attack_vec[i]->setNextAttack(attack_vec[i+1]);
			}
		}

		/*for (auto itor = (*attack).begin(); itor != (*attack).end();)
		{
			if (!(itor == (*attack).end()))
			{
				std::string this_key = attack.key().asString() + "_" + itor.key().asString() + cur_hero->getKey();
				itor++;
				if (itor != (*attack).end()) 
				{
					std::string next_key = attack.key().asString() + "_" + itor.key().asString() + cur_hero->getKey();
					Containers::Attack_table[this_key]->setNextAttack(Containers::Attack_table[next_key]);
				}	
			}
		}*/
	}
	
		//for()
		//new_attack->setNextAttack(Containers::texture_table["fireUp"];);

	/*


	"rockThrow" : {
	"1" : {
	"sprites" : {
	"right": {"0":"FireBallTMP", "1":3},
	"up": {"0":"FireBallTMPUp", "1":3},
	"down": {"0":"FireBallTMPDown", "1":3},
	"left": {"0":"FireBallTMPLeft", "1":3}
	},
	"set_name": -1,
	"set_dmg": 5,
	"set_speed" : 20,
	"set_base_dir" : 3,
	"set_cool_down" : 50,
	"set_stamina_cost" : 30,
	"set_pause" : 13,
	"set_destroy" : true,
	"set_Keep" : true,
	"set_width" : "cur_hero->body[0].getWidth()",
	"set_height" : "cur_hero->body[0].getHeight()",
	"set_duration" : 100,
	"set_ase_cost" : 25,
	"set_can_cancel" : false,
	"set_turn" : true
	}
	},

	//set the texture to the appropriate sprite 
	Containers::hero_table[name]->sprite.setTexture(Containers::texture_table[sprites["setTexture"]["0"].asString()]);
	Containers::hero_table[name]->sprite.setIdleTexture(Containers::texture_table[sprites["setIdleTexture"]["0"].asString()]);

	Containers::hero_table[name]->sprite.id_up = Containers::texture_table[sprites["id_up"]["0"].asString()];
	Containers::hero_table[name]->sprite.id_left = Containers::texture_table[sprites["id_left"]["0"].asString()];
	Containers::hero_table[name]->sprite.id_right = Containers::texture_table[sprites["id_right"]["0"].asString()];
	Containers::hero_table[name]->sprite.id_down = Containers::texture_table[sprites["id_down"]["0"].asString()];

	Attack* rockThrow = new Attack();
	rockThrow->setDmg(5);
	rockThrow->setSpeed(20);
	rockThrow->setDestroy(true);
	rockThrow->setDuration(100);
	rockThrow->setCoolDown(50);//120
	rockThrow->setPause(13);
	rockThrow->sprite.setTexture(Containers::texture_table["rockTex1"]);
	rockThrow->sprite.up = Containers::texture_table["rockTex1"];
	rockThrow->sprite.left = Containers::texture_table["rockTex1"];
	rockThrow->sprite.right = Containers::texture_table["rockTex1"];
	rockThrow->sprite.down = Containers::texture_table["rockTex1"];
	rockThrow->setCanCancel(false);
	Alex->addAttackType(rockThrow);

Attack* fireball = new Attack();
fireball->setDmg(20);
fireball->setSpeed(20);
fireball->setDestroy(true);
fireball->setDuration(100);
fireball->setCoolDown(120);
fireball->setPause(16);
fireball->setAseCost(25);
fireball->sprite.up = Containers::texture_table["fireUp"];
fireball->sprite.left = Containers::texture_table["fireLeft"];
fireball->sprite.right = Containers::texture_table["fire"];
fireball->sprite.down = Containers::texture_table["fireDown"];
fireball->setCanCancel(false);
Alex->addAttackType(fireball);

	//Alex->melee->sprite.setTexture(blank);
	Alex->melee->sprite.setTexture(Containers::texture_table["border"]);

	DialogueController::setPlayer(Alex);
	//vector<WorldObj*> recVec;
	Attack* spin = new Attack();
	spin->setDmg(15);
	spin->setSpeed(18);
	spin->setDestroy(false);
	spin->setDuration(7);
	spin->setBaseDir(4);
	spin->setCoolDown(100);
	spin->setPause(18);
	spin->setStaminaCost(30);
	spin->setTurn(true);
	spin->sprite.setTexture(Containers::texture_table["border"]);
	Alex->addAttackType(spin);
	Attack* spin2 = new Attack();
	spin2->setDmg(7);
	spin2->setSpeed(15);
	spin2->setDestroy(false);
	spin2->setDuration(7);
	spin2->setBaseDir(4);
	spin2->setCoolDown(0);
	spin2->setPause(23);
	spin2->setTurn(true);
	spin2->sprite.setTexture(Containers::texture_table["border"]);
	Alex->addAttackType(spin2);
	Attack* spin3 = new Attack();
	spin3->setDmg(7);
	spin3->setSpeed(15);
	spin3->setDestroy(false);
	spin3->setDuration(7);
	spin3->setBaseDir(4);
	spin3->setCoolDown(0);
	spin3->setPause(28);
	spin3->setTurn(true);
	spin3->sprite.setTexture(Containers::texture_table["border"]);
	Alex->addAttackType(spin3);
	Attack* spin4 = new Attack();
	spin4->setDmg(7);
	spin4->setSpeed(15);
	spin4->setDestroy(false);
	spin4->setDuration(7);
	spin4->setBaseDir(4);
	spin4->setCoolDown(0);
	spin4->setPause(33);
	spin4->setTurn(true);
	spin4->sprite.setTexture(Containers::texture_table["border"]);
	Alex->addAttackType(spin4);
	spin->setNextAttack(spin2);
	spin2->setNextAttack(spin3);
	spin3->setNextAttack(spin4);
	*/
}



void HeroConfig::init_hero_planner(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string name, int hero_id)
{
	//initializes action pool for given hero
	ActionConfig::import_config(gameplay_func, tBuffer, Containers::hero_table[name]);

	//initializes planner for given hero
	if (AIController::get_plan(hero_id) == nullptr) {
		Planner* heroPlanner = new Planner(Containers::hero_table[name]);
		AIController::set_plan(hero_id, heroPlanner);
	}
	
}

/*

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
*/