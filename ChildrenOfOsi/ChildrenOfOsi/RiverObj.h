#pragma once
#include "common.h"
#include "Line.h"
#include "Sprite.h"

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

