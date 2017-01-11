//------------------------------
//Eron Lake
//MyGameEngine
//main.cpp
//------------------------------

#include <iostream>

//toggles debug longging statements 
#define DEBUG 1

#if DEBUG 
#define LOG(input) std::cout << "LOG:" << input << std::endl
#else 
#define LOG(input) 

#endif

int main() {

	LOG("Hello world!");

	//pauses the program for viewing
	system("PAUSE");

	//demonstration of a meory leak
	while (true) {
		void* a = malloc(64);
		delete a;
	}

	return 0;
}

