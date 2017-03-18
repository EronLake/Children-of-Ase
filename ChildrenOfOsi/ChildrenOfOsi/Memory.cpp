#include "stdafx.h"
#include "Memory.h"

Memory::Memory()
{
}

Memory::Memory(int t, int frames, vector<NPC*> p, string cat, string cont, string where, int why, int when)
{
	type = t;
	if (type == ACTION && p.size() != 3)
	{
		LOG("Error: Action memory must have 3 people {Doer, Reciever, Instigator}");
		return;
	}
	else if (type == FACT && p.size() != 2)
	{
		LOG("Error: Fact memory must have 2 people {Who about, Info source}");
		return;
	}
	people = p;
	category = cat;
	content = cont;
	where = where;
	why = why;
	when = when;
	reason = "";
	time = frames;
}


Memory::~Memory()
{
}

void Memory::set_all(int t, int frames, vector<NPC*> p, string cat, string cont, string where, int why, int when)
{
	type = t;
	if (type == ACTION && p.size() != 3)
	{
		LOG("Error: Action memory must have 3 people {Doer, Reciever, Instigator}");
		return;
	}
	else if (type == FACT && p.size() != 2)
	{
		LOG("Error: Fact memory must have 2 people {Who about, Info source}");
		return;
	}
	people = p;
	category = cat;
	content = cont;
	where = where;
	why = why;
	when = when;
	reason = "";
	time = frames;
}

void Memory::setType(int t) {
	type = t;
}

int Memory::getType()
{
	return type;
}

void Memory::setPeople(vector<NPC*> p)
{
	people = p;
}

vector<NPC*> Memory::getPeople()
{
	return people;
}

void Memory::setCategory(string c)
{
	category = c;
}

string Memory::getCategory()
{
	return category;
}

void Memory::setContent(string c)
{
	content = c;
}

string Memory::getContent()
{
	return content;
}

void Memory::setWhere(string w)
{
	where = w;
}

string Memory::getWhere()
{
	return where;
}

void Memory::setWhy(int w)
{
	why = w;
}

int Memory::getWhy()
{
	return why;
}

void Memory::setWhen(int w)
{
	when = w;
}

int Memory::getWhen()
{
	return when;
}

void Memory::setReason(string r)
{
	reason = r;
}

string Memory::getReason()
{
	return reason;
}


void Memory::setTime(int t)
{
	time = t;
}

int Memory::getTime()
{
	return time;
}



//ACTIONS
void Memory::doneBy(NPC* w) 
{
	if (type != ACTION) {
		LOG("Error: not an Action memory");
		return;
	}
	people[0] = w;
}

NPC* Memory::doer()
{
	if (type != ACTION) {
		LOG("Error: not an Action memory");
		return nullptr;
	}
	return people[0];
}

void Memory::receivedBy(NPC* w) 
{
	if (type != ACTION) {
		LOG("Error: not an Action memory");
		return;
	}
	people[1] = w;

}

NPC* Memory::receiver()
{
	if (type != ACTION) {
		LOG("Error: not an Action memory");
		return nullptr;
	}
	return people[1];
}

void Memory::instigatedBy(NPC* w) 
{
	if (type != ACTION) {
		LOG("Error: not an Action memory");
		return;
	}
	people[2] = w;
}

NPC* Memory::instigator() 
{
	if (type != ACTION) {
		LOG("Error: not an Action memory");
		return nullptr;
	}
	return people[2];
}

void Memory::changeStatus(string s) 
{
	if (type != ACTION) {
		LOG("Error: not an Action memory");
		return;
	}
	if (s == "failure" || s == "success" || s == "started")
	{
		category = s;
	}
	else
	{
		LOG("Error: not a valid ACTION status");
	}
}

//string status();
//string name();


//FACTS
void Memory::isAbout(NPC* w) 
{
	if (type != FACT) {
		LOG("Error: not an Info memory");
		return;
	}
	people[0] = w;
}

NPC* Memory::who() 
{
	if (type != FACT) {
		LOG("Error: not an Info memory");
		return nullptr;
	}
	return people[0];
}

void Memory::toldBy(NPC* w) 
{
	if (type != FACT) {
		LOG("Error: not an Info memory");
		return;
	}
	people[1] = w;
}

NPC* Memory::source() 
{
	if (type != FACT) {
		LOG("Error: not an Info memory");
		return nullptr;
	}
	return people[1];
}
