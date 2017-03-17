#include "stdafx.h"

#include "WorldObj.h"

#include "GameWindow.h"

int WorldObj::idNum = 0;

void WorldObj::setX(float x)
{
	for (int i = 0; i < body.size(); i++) {
		body[i].setX(x-(loc.getXloc()-body[i].getX()));
	}
	loc.setXloc(x);
}

void WorldObj::setY(float y)
{
	for (int i = 0; i < body.size(); i++) {
		body[i].setY(y - (loc.getYloc() - body[i].getY()));
	}
	loc.setYloc(y);
}

void WorldObj::shiftX(float dist)
{
	loc.shiftXloc(dist);
	for (int i = 0; i < body.size(); i++) {
		body[i].setX(body[i].getX() + dist);
	}
	std::cout << name<<": Body X: " << body[0].getX() << " X: "<<loc.getXloc() << std::endl;
	std::cout << "X Offset" << body[0].getX()-loc.getXloc() << std::endl;
}

void WorldObj::shiftY(float dist)
{
	loc.shiftYloc(dist);
	for (int i = 0; i < body.size(); i++) {
		body[i].setY(body[i].getY()+dist);
	}
	std::cout << name << ": Body Y: " << body[0].getY() << " Y: " << loc.getYloc() << std::endl;
	std::cout << "Y Offset" << body[0].getY() - loc.getYloc() << std::endl;
}

void WorldObj::drawObj(float _x, float _y)
{
	osi::GameWindow::drawSprite(loc.getXloc()-_x, loc.getYloc()-_y, width, height, sprite);
}

void WorldObj::offsetBody(int i, float x1, float x2, float y1, float y2) {
	body[i].setX(body[i].getX()+x1);
	body[i].setY(body[i].getY() + y1);
	body[i].setWidth(body[i].getWidth() - (x1+x2));
	body[i].setHeight(body[i].getHeight() -(y1+y2));

}

void WorldObj::setDirWithBase(int od, bool update)
{
	if (update)baseDir = direction;
  if(od == 8) {
    if(baseDir == 2) od = 2;
    else if(baseDir == 4) od = 4;
    else if(baseDir == 6) od = 6;
  }
  else if(od == 2) {
    if(baseDir == 2) od = 8;
    else if(baseDir == 4) od = 6;
    else if(baseDir == 6) od = 4;
  }
  else if(od == 4) {
    if(baseDir == 2) od = 6;
    else if(baseDir == 4) od = 2;
    else if(baseDir == 6) od = 8;
  }
  else if(od == 6) {
    if(baseDir == 2) od = 4;
    else if(baseDir == 4) od = 8;
    else if(baseDir == 6) od = 2;
  }

  setDirection(od);
}

void WorldObj::face(WorldObj* other) {
	int f = 6;
	if (getX() > other->getX()) {
		if (getY() > other->getY()) {
			if (getX() > other->getX() + other->body[0].getWidth()) {
				f = 4;
			}
			else {
				f = 8;
			}
		}
		else {
			f = 2;
		}
	}
	setDirection(f);
}

//takes in a worldobj, returns a vector2f denoting where current obj is suppose to move to

void WorldObj::_print()
{
  std::cout << "Object Name" << getName() << std::endl;
  std::cout << "X Location" << getX() << std::endl;
  std::cout << "Y Location" << getY() << std::endl;
  std::cout << "Rotation Vector" << getX() << std::endl;
  std::cout << "Width" << getY() << std::endl;
  std::cout << "Height" << getX() << std::endl;
}
