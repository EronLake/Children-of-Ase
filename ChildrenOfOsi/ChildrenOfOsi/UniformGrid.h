#pragma once
#include "common.h"
#include "Line.h"


const int grid_size = 125;

class UniformGrid
{
public:
	UniformGrid();
	~UniformGrid();

	void insert_objs_to_grid(std::vector<Line*> objs);
	bool should_obj_move_grid(Line* obj);
	void move_obj_to_new_grid(Line* obj);
	void retrieve_objs_in_grid(std::vector<Line*> &listOfObj, Line* obj);



private:
	std::vector<Line*> grid[grid_size][grid_size];
	std::vector<Line*> objs_to_check;
};

