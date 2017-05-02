#pragma once
#include "common.h"
#include "Line.h"


const int grid_size = 20;	//each cell is 1250x1250

class UniformGrid
{
public:
	UniformGrid();
	~UniformGrid();

	void insert_objs_to_grid(std::vector<Line*> objs);
	std::vector<Line*> retrieve_objs_in_grid(std::vector<Line*> &listOfObj, Line* obj);
	void clear();

private:
	std::vector<Line*> grid[grid_size][grid_size];
};

