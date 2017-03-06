#pragma once
#include "common.h"

class Relationship {
private:
	int affinity;
	int notoriety;
	int strength;

	int aff_counter;
	int aff_max_change;
	int not_counter;
	int not_max_change;
	int str_counter;
	int str_max_change;

	bool changed;

public:
	Relationship();
	~Relationship();
	void setAffinity(int a);
	void addAffinity(int a);
	int getAffinity();
	void setNotoriety(int n);
	void addNotoriety(int n);
	int getNotoriety();
	void setStrength(int s);
	void addStrength(int s);
	int getStrength();
	bool isChanged() { return changed; };
	void setChanged(bool c) { changed = c; };
};