#include "stdafx.h"
#include "UniformGrid.h"


UniformGrid::UniformGrid()
{
	//clear the grid
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			grid[i][j].clear();
		}
	}
}


UniformGrid::~UniformGrid()
{
}

void UniformGrid::insert_objs_to_grid(std::vector<Line*> objs)
{
	//iterate through the lines and find the right grid to insert it into
	for (int i = 0; i < objs.size(); i++) {
		//find which grid the first point of the line belongs to.
		int xcoord = objs[i]->getP1().getX();
		int j = xcoord / 1250;
		int ycoord = objs[i]->getP1().getY();
		int k = ycoord / 1250;

		grid[j][k].push_back(objs[i]);

		//find which grid the second point of the line belongs to
		int xcoord2 = objs[i]->getP2().getX();
		int j2 = xcoord2 / 1250;
		int ycoord2 = objs[i]->getP2().getY();
		int k2 = ycoord2 / 1250;

		//if points belong to same column but different rows
		if (j2 == j && k2 != k) grid[j2][k2].push_back(objs[i]);
		//if points belong to same row but different column
		else if (j2 != j && k2 == k) grid[j2][k2].push_back(objs[i]);
		//if points belong to different rows and different columns
		else if (j2 != j && k2 != k) grid[j2][k2].push_back(objs[i]);
	}
	int count = 0;
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			for (int k = 0; k < grid[i][j].size(); k++) {
				count++;
			}
		}
	}
	std::cout << "There are " << count << " lines in the grid" << std::endl;
}

std::vector<Line*> UniformGrid::retrieve_objs_in_grid(std::vector<Line*>& listOfObj, Line * obj)
{
	//first find the cell that the obj belongs to on the grid
	int xcoord = obj->getP1().getX();
	int j = xcoord / 1250;
	int ycoord = obj->getP1().getY();
	int k = ycoord / 1250;

	listOfObj.insert(listOfObj.end(), grid[j][k].begin(), grid[j][k].end());

	//do the same thing for the second point of line
	int xcoord2 = obj->getP2().getX();
	int j2 = xcoord2 / 1250;
	int ycoord2 = obj->getP2().getY();
	int k2 = ycoord2 / 1250;

	//if points belong to same column but different rows
	if (j2 == j && k2 != k) {
		listOfObj.insert(listOfObj.end(), grid[j2][k2].begin(), grid[j2][k2].end());
		//for (int i = 0; i < grid[j2][k2].size(); i++) {
		//	if (std::find(listOfObj.begin(), listOfObj.end(), grid[j2][k2][i]) != listOfObj.end() == false) {
		//		listOfObj.push_back(grid[j2][k2][i]);
		//	}
		//}
	}
	//if points belong to same row but different column
	else if (j2 != j && k2 == k) {
		listOfObj.insert(listOfObj.end(), grid[j2][k2].begin(), grid[j2][k2].end());
		//for (int i = 0; i < grid[j2][k2].size(); i++) {
		//	if (std::find(listOfObj.begin(), listOfObj.end(), grid[j2][k2][i]) != listOfObj.end() == false) {
		//		listOfObj.push_back(grid[j2][k2][i]);
		//	}
		//}
	}
	//if points belong to different rows and different columns
	else if (j2 != j && k2 != k) {
		listOfObj.insert(listOfObj.end(), grid[j2][k2].begin(), grid[j2][k2].end());
		//for (int i = 0; i < grid[j2][k2].size(); i++) {
		//	if (std::find(listOfObj.begin(), listOfObj.end(), grid[j2][k2][i]) != listOfObj.end() == false) {
		//		listOfObj.push_back(grid[j2][k2][i]);
		//	}
		//}
	}

	return listOfObj;
}

void UniformGrid::clear()
{
	//iterate through the 2D array and clear all the vectors
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			grid[i][j].clear();
		}
	}
}
