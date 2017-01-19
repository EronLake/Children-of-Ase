#include "SplSoldier.h"
#include <iostream>
#include <string>
using namespace std;


SplSoldier::SplSoldier()
{
}

SplSoldier::SplSoldier(float x, float y, bool col) :Soldier(x, y, col)
{
	ase = 10;
	cout << "Ase: " << ase << endl;
}

SplSoldier::~SplSoldier()
{
}

void SplSoldier::setAse(int a)
{
	ase = a;
}

int SplSoldier::getAse()
{
	return ase;
}
