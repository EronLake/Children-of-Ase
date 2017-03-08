#include "stdafx.h"
#include "RiverObj.h"


RiverObj::RiverObj()
{
	
	Line l1(Point(685.465,1035.02), Point(1329.35,1068.96));
	lines.push_back(l1);
	Line l2(Point(1329.35, 1068.96), Point(2793.35, 1068.96));
	lines.push_back(l2);
	Line l3(Point(2793.35, 1068.96), Point(3418.03, 1255.64));
	lines.push_back(l3);
	Line l4(Point(3418.03, 1255.64), Point(4237.36, 1342.98));
	lines.push_back(l4);
	Line l5(Point(4237.36, 1342.98), Point(4716.16, 1461.77));
	lines.push_back(l5);
	Line l6(Point(4716.16, 1461.77), Point(5376.16, 1461.77));
	lines.push_back(l6);
	Line l7(Point(5376.16, 1461.77), Point(5835.5, 1597.11));
	lines.push_back(l7);
	Line l8(Point(5835.5, 1597.11), Point(6051.5, 1597.11));
	lines.push_back(l8);
	Line l9(Point(6051.5, 1597.11), Point(6501.62, 1524.99));
	lines.push_back(l9);
	Line l10(Point(6501.62, 1524.99), Point(6971.51, 1457.1));
	lines.push_back(l10);
	Line l11(Point(6971.51, 1457.1), Point(7378.18, 1503.77));
	lines.push_back(l11);
}


RiverObj::~RiverObj()
{
}

std::vector<Line> RiverObj::getLines()
{
	return lines;
}
