//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------

#include <iostream>
#include "WorldObj.h"
#include "Vector2f.h"

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
	int he = person.getHealth();
	bool al = person.getAlive();
	cout << "person is " << al << " with " << he << endl;
	//pauses the program for viewing
	system("PAUSE");

	//demonstration of a meory leak
	while (true) {
		void* a = malloc(64);
		delete a;
	}

	return 0;
}

