//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------

#include <iostream>
#include "WorldObj.h"

//toggles debug longging statements 
#define DEBUG 1

#if DEBUG 
#define LOG(input) std::cout << "LOG:" << input << std::endl
#else 
#define LOG(input) 

#endif

int main() {

	LOG("Hello world!");
	Hero person(20,0,true,100,true,5,10,40,64);
	//pauses the program for viewing
	system("PAUSE");

	//demonstration of a meory leak
	while (true) {
		void* a = malloc(64);
		delete a;
	}

	return 0;
}

