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

public:
	Relationship();
	~Relationship();
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