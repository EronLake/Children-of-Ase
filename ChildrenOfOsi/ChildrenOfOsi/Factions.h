#pragma once
class Factions
{
public:
	Factions();
	Factions(int randNum[]);
	~Factions();
	int getFRel(int f1, int f2);
	void setFRel(int f1, int f2, int rel);
private:
	int factions[5][5];
};

