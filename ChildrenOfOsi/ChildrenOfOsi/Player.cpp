#include "stdafx.h"
#include "Player.h"



Player::Player()
{

	this->move_to_flags.insert({ "Advise To Conquer", 0 });
	this->move_to_flags.insert({ "Advise To Ally With", 0 });
	this->move_to_flags.insert({ "Advise To Fight", 0 });
	this->move_to_flags.insert({ "Advise To Send Peace Offering To", 0 });

	can_spin = false;
	can_fire = false;
	can_move = true;
	can_move_counter = 30;
}

Player::Player(int name, float x, float y, bool col) :Hero(name, x, y, col)
{
	float speed = 6.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
	setType(6);
	cur_action = nullptr;

	this->move_to_flags.insert({ "Advise To Conquer", 0 });
	this->move_to_flags.insert({ "Advise To Ally With", 0 });
	this->move_to_flags.insert({ "Advise To Fight", 0 });
	this->move_to_flags.insert({ "Advise To Send Peace Offering To", 0 });

	can_spin= false;
	can_fire= false;
	can_move = true;
	can_move_counter = 30;
}

Player::Player(int name, Vector2f p_topLeft, float p_width, float p_height) :Hero(name, p_topLeft, p_width, p_height)
{
	float speed = 6.0F;
	NPC::setSpeed(speed);
	NPC::setDiagXSpeed(sqrt((speed*speed) / 2));
	NPC::setDiagYSpeed(sqrt((speed*speed) / 2));
	setType(6);
	cur_action = nullptr;

	this->move_to_flags.insert({ "Advise To Conquer", 0 });
	this->move_to_flags.insert({ "Advise To Ally With", 0 });
	this->move_to_flags.insert({ "Advise To Fight", 0 });
	this->move_to_flags.insert({ "Advise To Send Peace Offering To", 0 });

	can_spin = false;
	can_fire = false;
	can_move = true;
	can_move_counter = 30;
}


Player::~Player()
{
}

void Player::setTalkDist(float dist)
{
	distance = dist;
	talk.setX((*this).getX() - dist);
	talk.setY((*this).getY() - dist);
	talk.setWidth((*this).getWidth() + (2 * dist));
	talk.setHeight((*this).getHeight() + (2 * dist));
}

void Player::updateTalk()
{
	talk.setX((*this).getX() - distance);
	talk.setY((*this).getY() - distance);
	talk.setWidth((*this).getWidth() + (2 * distance));
	talk.setHeight((*this).getHeight() + (2 * distance));
}

/*filters the move-to options that the player has available when speaking to heroes*/
void Player::filter_move_to(Hero* npc) {
	//turn off all move to flags if notoriety less than 60
	if (npc->rel[this->name]->getNotoriety() < 55) {
		for (auto itor = this->move_to_flags.begin(); itor != this->move_to_flags.end(); ++itor) {
			itor->second = 0;
		}
	}
	else {
		this->move_to_flags["Advise To Fight"] = 1; //turn fight flag on
		this->move_to_flags["Advise To Send Peace Offering To"] = 1; //turn peace offering flag on
		
		if (npc->rel[this->name]->getNotoriety() > 60 &&
			npc->rel[this->name]->getAffinity() > 60)
			this->move_to_flags["Advise To Ally With"] = 1; //turn on form alliance flag

		if(npc->rel[this->name]->getNotoriety() > 60 &&
			npc->rel[this->name]->getStrength() > 60)
		{
			this->move_to_flags["Advise To Conquer"] = 1;	//turn on conquer flag
		}
	}
}

void Player::activate_exalted_form()
{

	Json::Value root;
	Json::Reader reader;


	std::ifstream file("hero_config.json");

	file >> root;

	//these sprites all heroes have
	auto sprites = root["Shango"]["sprites"];

	//set the texture to the appropriate sprite 
	Containers::hero_table["Shango"]->sprite.setTexture(Containers::texture_table[sprites["exalted_setTexture"]["0"].asString()]);
	Containers::hero_table["Shango"]->sprite.setIdleTexture(Containers::texture_table[sprites["exalted_setIdleTexture"]["0"].asString()]);

	Containers::hero_table["Shango"]->sprite.id_up = Containers::texture_table[sprites["exalted_id_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.id_left = Containers::texture_table[sprites["exalted_id_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.id_right = Containers::texture_table[sprites["exalted_id_right"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.id_down = Containers::texture_table[sprites["exalted_id_down"]["0"].asString()];

	//Containers::hero_table[name]->sprite.up = Containers::texture_table[sprites["exalted_walk_up"]["0"].asString()];
	//Containers::hero_table[name]->sprite.down = Containers::texture_table[sprites["exalted_walk_down"]["0"].asString()];
	//Containers::hero_table[name]->sprite.left = Containers::texture_table[sprites["exalted_walk_left"]["0"].asString()];
	//Containers::hero_table[name]->sprite.right = Containers::texture_table[sprites["exalted_walk_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.up = Containers::texture_table[sprites["exalted_sprint_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.down = Containers::texture_table[sprites["exalted_sprint_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.left = Containers::texture_table[sprites["exalted_sprint_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.right = Containers::texture_table[sprites["exalted_sprint_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.atk_up = Containers::texture_table[sprites["exalted_atk_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk_down = Containers::texture_table[sprites["exalted_atk_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk_left = Containers::texture_table[sprites["exalted_atk_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk_right = Containers::texture_table[sprites["exalted_atk_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.atk2_up = Containers::texture_table[sprites["exalted_atk2_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk2_down = Containers::texture_table[sprites["exalted_atk2_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk2_left = Containers::texture_table[sprites["exalted_atk2_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk2_right = Containers::texture_table[sprites["exalted_atk2_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.spin_up = Containers::texture_table[sprites["exalted_spin_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.spin_down = Containers::texture_table[sprites["exalted_spin_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.spin_left = Containers::texture_table[sprites["exalted_spin_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.spin_right = Containers::texture_table[sprites["exalted_spin_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.breathe_up = Containers::texture_table[sprites["exalted_breathe_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.breathe_down = Containers::texture_table[sprites["exalted_breathe_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.breathe_left = Containers::texture_table[sprites["exalted_breathe_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.breathe_right = Containers::texture_table[sprites["exalted_breathe_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.hurt_up = Containers::texture_table[sprites["exalted_hurt_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.hurt_down = Containers::texture_table[sprites["exalted_hurt_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.hurt_left = Containers::texture_table[sprites["exalted_hurt_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.hurt_right = Containers::texture_table[sprites["exalted_hurt_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.death_up = Containers::texture_table[sprites["exalted_death_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.death_down = Containers::texture_table[sprites["exalted_death_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.death_left = Containers::texture_table[sprites["exalted_death_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.death_right = Containers::texture_table[sprites["exalted_death_right"]["0"].asString()];
}


void Player::deactivate_exalted_form()
{

	Json::Value root;
	Json::Reader reader;


	std::ifstream file("hero_config.json");

	file >> root;

	//these sprites all heroes have
	auto sprites = root["Shango"]["sprites"];

	//set the texture to the appropriate sprite 
	Containers::hero_table["Shango"]->sprite.setTexture(Containers::texture_table[sprites["setTexture"]["0"].asString()]);
	Containers::hero_table["Shango"]->sprite.setIdleTexture(Containers::texture_table[sprites["setIdleTexture"]["0"].asString()]);

	Containers::hero_table["Shango"]->sprite.id_up = Containers::texture_table[sprites["id_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.id_left = Containers::texture_table[sprites["id_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.id_right = Containers::texture_table[sprites["id_right"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.id_down = Containers::texture_table[sprites["id_down"]["0"].asString()];

	//Containers::hero_table[name]->sprite.up = Containers::texture_table[sprites["walk_up"]["0"].asString()];
	//Containers::hero_table[name]->sprite.down = Containers::texture_table[sprites["walk_down"]["0"].asString()];
	//Containers::hero_table[name]->sprite.left = Containers::texture_table[sprites["walk_left"]["0"].asString()];
	//Containers::hero_table[name]->sprite.right = Containers::texture_table[sprites["walk_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.up = Containers::texture_table[sprites["sprint_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.down = Containers::texture_table[sprites["sprint_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.left = Containers::texture_table[sprites["sprint_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.right = Containers::texture_table[sprites["sprint_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.atk_up = Containers::texture_table[sprites["atk_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk_down = Containers::texture_table[sprites["atk_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk_left = Containers::texture_table[sprites["atk_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk_right = Containers::texture_table[sprites["atk_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.atk2_up = Containers::texture_table[sprites["atk2_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk2_down = Containers::texture_table[sprites["atk2_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk2_left = Containers::texture_table[sprites["atk2_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.atk2_right = Containers::texture_table[sprites["atk2_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.spin_up = Containers::texture_table[sprites["spin_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.spin_down = Containers::texture_table[sprites["spin_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.spin_left = Containers::texture_table[sprites["spin_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.spin_right = Containers::texture_table[sprites["spin_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.breathe_up = Containers::texture_table[sprites["breathe_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.breathe_down = Containers::texture_table[sprites["breathe_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.breathe_left = Containers::texture_table[sprites["breathe_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.breathe_right = Containers::texture_table[sprites["breathe_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.hurt_up = Containers::texture_table[sprites["hurt_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.hurt_down = Containers::texture_table[sprites["hurt_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.hurt_left = Containers::texture_table[sprites["hurt_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.hurt_right = Containers::texture_table[sprites["hurt_right"]["0"].asString()];

	Containers::hero_table["Shango"]->sprite.death_up = Containers::texture_table[sprites["death_up"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.death_down = Containers::texture_table[sprites["death_down"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.death_left = Containers::texture_table[sprites["death_left"]["0"].asString()];
	Containers::hero_table["Shango"]->sprite.death_right = Containers::texture_table[sprites["death_right"]["0"].asString()];
}

