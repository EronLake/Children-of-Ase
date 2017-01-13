//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------

#include <iostream>
#include "WorldObj.h"
#include "Vector2f.h"
#include "Player.h"

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
	Hero person(20,0,true);
	person.setHealth(-10);
	person.setAlive(false);
	cout << "person is " << person.getAlive() << " with " << person.getHealth() << endl;
	cout<<"at location " << person.getLoc().getXloc() << " , " << person.getLoc().getYloc() << endl;
	Player me(30, 32, true);
	//pauses the program for viewing
	system("PAUSE");

	//demonstration of a meory leak
	while (true) {
		void* a = malloc(64);
		delete a;
	}

	return 0;
}

