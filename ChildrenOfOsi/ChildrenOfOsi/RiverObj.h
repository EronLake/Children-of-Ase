#pragma once
#include "common.h"
#include "Line.h"
#include "Sprite.h"

class RiverObj
{
public:
	RiverObj();
	~RiverObj();
	std::vector<Line*> getLines();
	void initialize_lines();
	

private:
	// BE SURE TO FREE THIS AT THE VERY END OF THE GAME
	std::vector<Line*> lines;
};

