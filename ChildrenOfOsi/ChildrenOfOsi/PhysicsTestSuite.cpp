#include "stdafx.h"
#include "PhysicsTestSuite.h"
#include "Movement.h"



PhysicsTestSuite::PhysicsTestSuite() 
{
	
	
	LOG("AudioTestSuite Object Constructed");
}


PhysicsTestSuite::~PhysicsTestSuite()
{
	LOG("AudioTestSuite Object Destroyed");
}

bool PhysicsTestSuite::execute_tests() {
	bool pass = true;
	if (test_movement())
	{
		LOG("Movement Test: " << "PASS");
	}
	else
	{
		LOG("Movement Test: " << "FAIL");
		pass = false;
	}
	if (test_collision()) 
	{
		LOG("Collision Test: " << "PASS");

	}
	else
	{
		LOG("Collision Test: " << "FAIL");
		pass = false;

	}
	return pass;
}
bool PhysicsTestSuite::test_movement() {
	WorldObj* screen = new WorldObj(Vector2f(0.0, 0.0), 960U, 540U);
	QuadTree* t = new QuadTree(0, *screen);
	RiverObj* myriv = new RiverObj();
	myriv->initialize_lines();
	std::vector<Line*> l;
	UniformGrid<Line>* grid = new UniformGrid<Line>();
	UniformGrid<WorldObj>* grid2 = new UniformGrid<WorldObj>();
	Movement* movetests = new Movement(t,grid,myriv, grid2);

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	//check move up
	WorldObj* x = new WorldObj();
	x->setX(.5);
	x->setY(.5);
	movetests->move_up(x);
	//up is negative y, down is positive y
	if (x->getY() > .5) {
		//fail if move down
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
	
		up = false;
	}
	else {
		//succeed
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		up = true;
	}

	//check move down
	x = new WorldObj();
	x->setX(.5);
	x->setY(.5);
	movetests->move_down(x);
	if (x->getY() < .5) {
		//fail if move up
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;

		down = false;
	}
	else {
		//succeed
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		down = true;
	}

	//check move left
	x = new WorldObj();
	x->setX(.5);
	x->setY(.5);
	movetests->move_left(x);
	if (x->getX() > .5) {
		//////cout << endl;
		//fail if move right
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;

		left = false;
	}
	else {
		//succeed
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		left = true;
	}

	//check move right
	x = new WorldObj();
	x->setX(.5);
	x->setY(.5);
	movetests->move_right(x);
	if (x->getY() < .5) {
		//fail if move down
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;

		right = false;
	}
	else {
		//succeed
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		right = true;
	}
	if (up && down && left && right) {
		return true;
	}
	else {
		return false;
	}
}
bool PhysicsTestSuite::test_collision() {
	WorldObj* screen = new WorldObj(Vector2f(0.0, 0.0), 960U, 540U);
	QuadTree* t = new QuadTree(0, *screen);
	RiverObj* rivObj = new RiverObj();
	std::vector<Line*> l;
	UniformGrid<Line>* grid = new UniformGrid<Line>();
	UniformGrid<WorldObj>* grid2 = new UniformGrid<WorldObj>();
	Movement* movetests = new Movement(t,grid,rivObj, grid2);
	bool result;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	//collide up
	WorldObj* x = new WorldObj();
	WorldObj* y = new WorldObj();
	x->setX(.5);
	x->setY(.5);
	y->setX(.5);
	y->setY(0);
	result = movetests->move_up(x);
	if (result) {
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		up = false;
	}
	else {
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		up = true;
	}

	//collide down
	x = new WorldObj();
	y = new WorldObj();
	x->setX(.5);
	x->setY(.5);
	y->setX(.5);
	y->setY(1);
	result = movetests->move_down(x);
	if (result) {
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		down = false;
	}
	else {
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		down = true;
	}

	//collide left
	x = new WorldObj();
	y = new WorldObj();
	x->setX(.5);
	x->setY(.5);
	y->setX(0);
	y->setY(.5);
	result = movetests->move_left(x);
	if (result) {
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		left = false;
	}
	else {
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		left = true;
	}

	//collide right
	x = new WorldObj();
	y = new WorldObj();
	x->setX(.5);
	x->setY(.5);
	y->setX(1);
	y->setY(.5);
	result = movetests->move_right(x);
	if (result) {
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		right = false;
	}
	else {
		//////cout << endl;
		//////cout << "Current Location" << endl;
		x->_print();
		//////cout << "Starting Location = (.5,.5)" << endl;
		right = true;
	}


	if (up && down && left && right) {
		return true;
	}
	else {
		return false;
	}
}