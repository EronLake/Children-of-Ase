#include "stdafx.h"
#include "Player.h"



Player::Player()
{

	this->move_to_flags.insert({ "Advise To Conquer", 0 });
	this->move_to_flags.insert({ "Advise To Ally With", 0 });
	this->move_to_flags.insert({ "Advise To Fight", 0 });
	this->move_to_flags.insert({ "Advise To Send Peace Offering", 0 });
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
	this->move_to_flags.insert({ "Advise To Send Peace Offering", 0 });
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
	this->move_to_flags.insert({ "Advise To Send Peace Offering", 0 });
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
	if (npc->rel[this->name]->getNotoriety() < 60) {
		for (auto itor = this->move_to_flags.begin(); itor != this->move_to_flags.end(); ++itor) {
			itor->second = 0;
		}
	}
	else {
		this->move_to_flags["Advise To Fight"] = 1; //turn fight flag on
		this->move_to_flags["Advise To Send Peace Offering"] = 1; //turn peace offering flag on
		
		if (npc->rel[this->name]->getNotoriety() > 70 &&
			npc->rel[this->name]->getAffinity() > 70)
			this->move_to_flags["Advise To Form Alliance"] = 1; //turn on form alliance flag

		if(npc->rel[this->name]->getNotoriety() > 70 &&
			npc->rel[this->name]->getStrength() > 70)
		{
			this->move_to_flags["Advise To Conquer"] = 1;	//turn on conquer flag
		}
	}
}
