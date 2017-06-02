#pragma once
#include "common.h"

class Relationship {
private:
	int affinity;
	int notoriety;
	int strength;
	int affEstimate;
	int notorEstimate;
	int strEstimate;

	int aff_counter;
	int aff_max_change;
	int not_counter;
	int not_max_change;
	int str_counter;
	int str_max_change;

	int changed;

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
	int isChanged() { return changed; };
	void setChanged(int c) { changed = c; };

	
	void setAffEstimate(int a) { affEstimate = a; };
	void addAffEstimate(int a) {affEstimate += a; if (affEstimate > 100) { affEstimate = 100; }else if (affEstimate < 0)affEstimate = 0;};
	int getAffEstimate() { return affEstimate; };
	void setNotorEstimate(int n) { notorEstimate = n; };
	void addNotorEstimate(int n) { notorEstimate += n; if (notorEstimate > 100) { notorEstimate = 100; }else if (notorEstimate < 0)notorEstimate = 0;};
	int getNotorEstimate() { return notorEstimate; };
	void setStrEstimate(int s) { strEstimate = s; };
	void addStrEstimate(int s) { strEstimate += s; if (strEstimate > 100) { strEstimate = 100; }else if (strEstimate < 0)strEstimate = 0;};
	int getStrEstimate() { return strEstimate; };
};