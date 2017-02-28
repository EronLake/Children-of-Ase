#pragma once
#include "common.h"

class Relationship {
private:
	int affinity;
	int notoriety;
	int strength;

public:
	Relationship(int p_affi = 50, int p_noto = 50, int p_str = 50);
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

	friend std::ostream& operator<<(std::ostream& os, const Relationship& relation);
};