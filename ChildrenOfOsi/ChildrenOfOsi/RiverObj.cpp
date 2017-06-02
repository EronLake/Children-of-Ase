#include "stdafx.h"
#include "RiverObj.h"


RiverObj::RiverObj()
{
}


RiverObj::~RiverObj()
{
}

std::vector<Line*> RiverObj::getLines()
{
	return lines;
}

void RiverObj::initialize_lines() {
	lines.clear();
	std::ifstream rivFile;
	rivFile.open("rivLine.txt");
	int a, b, c, d;
	while (rivFile >> a >> b >> c >> d) {
		lines.push_back(new Line(Point(a, b), Point(c, d)));
	}
	rivFile.close();
	rivFile.clear();

	rivFile.open("oasis.txt");
	while (rivFile >> a >> b >> c >> d) {
		lines.push_back(new Line(Point(a, b), Point(c, d)));
	}
	rivFile.close();
	rivFile.clear();

	if (!RIVER_COLLIDE) lines.clear();
	//std::cout << "SIZE OF THE LINES IS " << lines.size() << std::endl;
	
}
