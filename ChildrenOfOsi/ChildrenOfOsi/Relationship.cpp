#include "stdafx.h"
#include "Relationship.h"

Relationship::Relationship()
{
	affinity = 50;
	notoriety = 50;
	strength = 50;
	affEstimate=50;
	notorEstimate=50;
	strEstimate=50;

	changed = false;

	aff_counter = 0;
	aff_max_change = 10;
	not_counter = 0;
	not_max_change = 10;
	str_counter = 0;
	str_max_change = 10;

	LOG("Relationship Object Constructed");
}


Relationship::~Relationship()
{
	LOG("Relationship Object Destroyed");
}

void Relationship::setAffinity(int a)
{
	aff_counter += (a - affinity); 
	changed += (a - affinity);
	//affinity = a;
	/*if (aff_counter > aff_max_change) {
		aff_counter = 0;
		changed = true;
	}*/
}
void Relationship::addAffinity(int a)
{
	affinity += a; 
	changed += a;
	if (affinity > 100) {
		affinity = 100;
	} else if (affinity < 0)affinity = 0;
	//aff_counter += a;
	/*if (aff_counter > aff_max_change) {
		aff_counter = 0;
		changed = true;
	}*/
}
int Relationship::getAffinity()
{
	return affinity;
}
void Relationship::setNotoriety(int n)
{
	not_counter += (n - notoriety); 
	changed += (n - notoriety);
	//notoriety = n;
	/*if (not_counter > not_max_change) {
		not_counter = 0;
		changed = true;
	}*/
}
void Relationship::addNotoriety(int n)
{
	notoriety += n; 
	changed += n;
	if (notoriety > 100) {
		notoriety = 100;
	}
	else if (notoriety < 0)notoriety = 0;
	//not_counter += n;
	/*if (not_counter > not_max_change) {
		not_counter = 0;
		changed = true;
	}*/
}
int Relationship::getNotoriety()
{
	return notoriety;
}
void Relationship::setStrength(int s)
{
	str_counter += (s - strength); 
	changed += (s - strength);
	//strength = s;
	/*if (str_counter > str_max_change) {
		str_counter = 0;
		changed = true;
	}*/
}
void Relationship::addStrength(int s)
{
	strength += s; 
	changed += s;
	if (strength > 100) {
		strength = 100;
	}
	else if (strength < 0)strength = 0;
	//str_counter += s;
	/*if (str_counter > str_max_change) {
		str_counter = 0;
		changed = true;
	}*/
}
int Relationship::getStrength()
{
	return strength;
}
