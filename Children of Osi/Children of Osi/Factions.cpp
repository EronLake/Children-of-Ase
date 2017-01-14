#include "Factions.h"
#include <stdio.h>   
#include <stdlib.h>   
#include <iostream>
#include <string>
using namespace std;

Factions::Factions() 
{
}

Factions::Factions(int ranNum[])
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			factions[i][j] = -2;
		}
	}
	int f = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == j)factions[i][j] = 3;
			if (factions[j][i] == -2) {
				factions[i][j] = ranNum[f];
				f++;
			}
			else factions[i][j] = factions[j][i];
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			//cout << "Faction " << i << " is a " << factions[j][i] << " with faction " << j << endl;
		}
	}
}


Factions::~Factions()
{
}

int Factions::getFRel(int f1, int f2)
{
	return factions[f1][f2];
}

void Factions::setFRel(int f1, int f2, int rel)
{
	factions[f1][f2]=rel;
}
