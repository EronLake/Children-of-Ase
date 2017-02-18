#include "stdafx.h"
#include "Wrapper.h"


Wrapper::Wrapper()
{
}

Wrapper::Wrapper(Player* p)
{
	player = p;
	type = 6;
	talk = &p->talk;
	sprite = &p->sprite;
}

Wrapper::Wrapper(Hero* h)
{
	hero = h;
	type = 5;
	sprite = &h->sprite;
}

Wrapper::Wrapper(SplSoldier* sp)
{
	special = sp;
	type = 4;
	sprite = &sp->sprite;
}

Wrapper::Wrapper(Soldier* s)
{
	soldier = s;
	type = 3;
	sprite = &s->sprite;
}

Wrapper::Wrapper(NPC* n)
{
	npc = n;
	type = 2;
	sprite = &n->sprite;
}

Wrapper::Wrapper(LivingObj* l)
{
	living = l;
	type = 1;
	sprite = &l->sprite;
}

Wrapper::Wrapper(WorldObj* w)
{
	world = w;
	type = 0;
	sprite = &w->sprite;
}

Wrapper::~Wrapper()
{
}
