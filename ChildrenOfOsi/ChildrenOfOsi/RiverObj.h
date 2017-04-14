#pragma once
#include "common.h"
#include "Line.h"

class RiverObj
{
public:
	RiverObj();
	~RiverObj();
	std::vector<Line> getLines();
	void initialize_lines();
	

private:
	std::vector<Line> lines;
};

