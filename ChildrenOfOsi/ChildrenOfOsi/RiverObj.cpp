#include "stdafx.h"
#include "RiverObj.h"


RiverObj::RiverObj()
{
	
}


RiverObj::~RiverObj()
{
}

std::vector<Line> RiverObj::getLines()
{
	return lines;
}

void RiverObj::initialize_lines() {
	lines.clear();
	std::ifstream rivFile("rivLine.txt");
	int a, b, c, d;
	while (rivFile >> a >> b >> c >> d) {
		lines.push_back(Line(Point(a, b), Point(c, d)));
	}

	for (int i = 0; i < lines.size(); i++) {
		//std:://cout << lines[i].getP1().getX() << ", " <<  lines[i].getP1().getY() << ", " << lines[i].getP2().getX() << ", " << lines[i].getP2().getY() << std::endl;
	}

	//std:://cout << "TOTAL SIZE OF THE LINES VECTOR IS " << lines.size() << std::endl;
	
}
