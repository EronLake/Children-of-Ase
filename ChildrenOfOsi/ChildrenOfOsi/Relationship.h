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
	void setAffinity(int a) { affinity = a; };
	void addAffinity(int a) { affinity += a; };
	int getAffinity() { return affinity; };
	void setNotoriety(int n) { notoriety = n; };
	void addNotoriety(int n) { notoriety += n; };
	int getNotoriety() { return notoriety; };
	void setStrength(int s) { strength = s; };
	void addStrength(int s) { strength += s; };
	int getStrength() { return strength; };
	void setAffEstimate(int a) { affEstimate = a; };
	void addAffEstimate(int a) { affEstimate += a; };
	int getAffEstimate() { return affEstimate; };
	void setNotorEstimate(int n) { notorEstimate = n; };
	void addNotorEstimate(int n) { notorEstimate += n; };
	int getNotorEstimate() { return notorEstimate; };
	void setStrEstimate(int s) { strEstimate = s; };
	void addStrEstimate(int s) { strEstimate += s; };
	int getStrEstimate() { return strEstimate; };
};