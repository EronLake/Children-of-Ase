#include "WorldObj.h"
#include <iostream>
#include <string>

using namespace std;



WorldObj::WorldObj()
{
}

WorldObj::WorldObj(float x, float y, bool col)
{
	loc.setXloc(x);
	loc.setYloc(y);
	rotation.setXloc(1);
	rotation.setYloc(1);
	collision = col;
	cout <<"X-Loc: "<< loc.getXloc() << endl;
	cout << "Y-Loc: " << loc.getYloc() << endl;
	cout << "Rotation: " << rotation.getXloc()<<" , " << rotation.getYloc()<< endl;
	cout << "Collision: " << collision << endl;
}

WorldObj::~WorldObj()
{
}

Vector2f WorldObj::getLoc()
{
	return loc;
}

Vector2f WorldObj::getRot()
{
	return rotation;
}

void WorldObj::setLoc(Vector2f l)
{
	loc = l;
}

void WorldObj::setRot(Vector2f r)
{
	rotation = r;
}

void WorldObj::setCollision(bool c)
{
	collision = c;
}

bool WorldObj::getCollision()
{
	return collision;
}

/*void WorldObj::setName(string na)
{
	name=na;
}

string WorldObj::getName()
{
	return name;
}
*/
