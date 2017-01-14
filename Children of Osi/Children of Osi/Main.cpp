//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------

#include <stdio.h>   
#include <stdlib.h>     
#include <time.h>
#include <iostream>
#include "WorldObj.h"
#include "LivingObj.h"
#include "NPC.h"
#include "Soldier.h"
#include "SplSoldier.h"
#include "Hero.h"
#include "Vector2f.h"
#include "Player.h"
#include "Factions.h"

//toggles debug longging statements 
#define DEBUG 1

#if DEBUG 
#define LOG(input) std::cout << "LOG:" << input << std::endl
#else 
#define LOG(input) 

#endif

using namespace std;

int main() {
	LOG("Hello world!");
	srand(time(NULL));
	int rInt[10];
	for (int i = 0; i < 10; i++) {
		rInt[i] = rand() % 4 - 1;
	}
	Factions fac(rInt);
	Hero person(20,0,true);
	person.setHealth(-10);
	person.setAlive(false);
	cout << "person is " << person.getAlive() << " with " << person.getHealth() << endl;
	cout<<"at location " << person.getX() << " , " << person.getY() << endl;
	Player me(30, 32, true);
	NPC citizen(22, 2, true);
	citizen.setHealth(10);
	person.setAtk(2);
	person.goAtk(&citizen);
	cout << "Citizen's Health: " << citizen.getHealth() << endl;
	cout << fac.getFRel(citizen.getFaction(), person.getFaction()) << endl;
	fac.setFRel(citizen.getFaction(), person.getFaction(), -1);
	cout << fac.getFRel(citizen.getFaction(), person.getFaction()) << endl;
	citizen.shiftX(2);
	citizen.shiftY(3);
	cout << "citizen is now at: " << citizen.getX() << " , " << citizen.getY() << endl;
	//pauses the program for viewing
	system("PAUSE");

	//demonstration of a meory leak
	/*while (true) {
		void* a = malloc(64);
		delete a;
	}*/

	return 0;
}

