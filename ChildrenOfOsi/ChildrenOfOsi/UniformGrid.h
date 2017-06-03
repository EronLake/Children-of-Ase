#pragma once
#include "stdafx.h"
#include "common.h"
#include "Line.h"


const int grid_size = 20;	//each cell is 1250x1250

template <class T>
class UniformGrid
{
public:
	UniformGrid();
	~UniformGrid();
	void insert_objs_to_grid(std::vector<T*> objs);
	void insert_worldobj_to_grid(std::vector<T*> objs);
	void clear_and_reinsert(std::vector<T*> objs);
	std::vector<T*> retrieve_objs_in_grid(std::vector<T*> &listOfObj, T* obj);
	std::vector<T*> retrieve_worldobj_in_grid(std::vector<T*> &listOfObj, T* obj);


	void clear();

private:
	std::vector<T*> grid[grid_size+1][grid_size+1];
	int num_of_elements;
};

template <class T>
UniformGrid<T>::UniformGrid<T>()
{
	//clear the grid
	for (int i = 0; i <= grid_size; i++) {
		for (int j = 0; j <= grid_size; j++) {
			grid[i][j].clear();
		}
	}
	num_of_elements = 0;
}

template <class T>
UniformGrid<T>::~UniformGrid<T>()
{
}

template <class T>
void UniformGrid<T>::insert_worldobj_to_grid(std::vector<T*> objs)
{
	//iterate  thru all the objects
	for (int i = 0; i < objs.size(); i++) {
		//first find the cell that the obj belongs to on the grid
		int xcoord = objs[i]->body[0].getX();
		int j = xcoord / 1250;
		int ycoord = objs[i]->body[0].getY();
		int k = ycoord / 1250;

		objs[i]->grid_location.first = j;
		objs[i]->grid_location.second = k;

		//cout << "j and k are " << j << ", " << k << endl;
		grid[j][k].push_back(objs[i]);
		num_of_elements++;
	}
}

template <class T>
void UniformGrid<T>::clear_and_reinsert(std::vector<T*> objs)
{
	for (int i = 0; i < objs.size(); i++) {
		int current_grid_j = objs[i]->grid_location.first;
		int current_grid_k = objs[i]->grid_location.second;
		//cout << "old j is " << current_grid_j << " and old k is " << current_grid_k << endl;

		//first find the cell that the obj belongs to on the grid
		int xcoord = objs[i]->body[0].getX();
		int j = xcoord / 1250;
		int ycoord = objs[i]->body[0].getY();
		int k = ycoord / 1250;

		//cout << "curr j is " << j << " and curr k is " << k << endl;


		//if grid loc is incorrect, remove from current grid 
		if (current_grid_j != j || current_grid_k != k) {
			//cout << "ABOUT TO REMOVE ITEM" << endl;
			//int oldsize = grid[current_grid_j][current_grid_k].size();
			//cout << "grid old size is " << grid[current_grid_j][current_grid_k].size() << endl;
			//auto position = std::find(grid[current_grid_j][current_grid_k].begin(), grid[current_grid_j][current_grid_k].end(), objs[i]);
			//if (position == grid[current_grid_j][current_grid_k].end()) {
			//	cout << "COULDNT FIND THE ELEMENT" << endl;
			//	cout << "element name is " << objs[i]->getName() << endl;
			//	system("PAUSE");
			//}
			grid[current_grid_j][current_grid_k].erase(std::remove(grid[current_grid_j][current_grid_k].begin(), grid[current_grid_j][current_grid_k].end(), objs[i]), grid[current_grid_j][current_grid_k].end());
			//int newsize = grid[current_grid_j][current_grid_k].size();
			//cout << "grid new size is " << grid[current_grid_j][current_grid_k].size() << endl;
			//if (oldsize == newsize) {
			//	void _CrtDbgBreak(void);
			//	//system("PAUSE");
			//}
			//cout << "old grid old size is " << grid[j][k].size() << endl;
			grid[j][k].push_back(objs[i]);
			objs[i]->grid_location.first = j;
			objs[i]->grid_location.second = k;
			//cout << "old grid new size is " << grid[j][k].size() << endl;

			//num_of_elements--;
		}

		////add obj to new grid
		//grid[j][k].push_back(objs[i]);
		//num_of_elements++;
	}

	int count = 0;
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			for (int k = 0; k < grid[i][j].size(); k++) {
				count++;
			}
		}
	}
	//std::cout << "There are " << count << " objs in the grid" << std::endl;
}

template <class T>
std::vector<T*> UniformGrid<T>::retrieve_worldobj_in_grid(std::vector<T*> &listOfObj, T* obj)
{

	if (num_of_elements == 0) return listOfObj;

	//first find the cell that the obj belongs to on the grid
	int xcoord = obj->body[0].getX();
	int j = xcoord / 1250;
	int ycoord = obj->body[0].getY();
	int k = ycoord / 1250;

	//j and k would range from 0 to 20, 0 being top left part of map, and 20 being bottom right. It's really 0 and 19. 20 lies exactly at 25000 px.

	if (j > 0 && k > 0) {
		//go around the cell and insert all obj in. square shape
		int temp1 = j, temp2 = k;
		temp1--; temp2--;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp1++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp1++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp2++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp2++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp1--;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp1--;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp2--;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());

		listOfObj.insert(listOfObj.end(), grid[j][k].begin(), grid[j][k].end());
	}
	else if (j == 0 && k != 0) {
		int temp1 = j, temp2 = k;
		temp2--;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp1++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp2++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp2++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp1--;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());

		listOfObj.insert(listOfObj.end(), grid[j][k].begin(), grid[j][k].end());
	}
	else if (k == 0 || j != 0) {
		int temp1 = j, temp2 = k;
		temp1--;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp2++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp1++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp1++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp2--;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());

		listOfObj.insert(listOfObj.end(), grid[j][k].begin(), grid[j][k].end());
	}
	else {
		//j and k are both 0
		int temp1 = j, temp2 = k;
		temp1++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp2++;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());
		temp1--;
		listOfObj.insert(listOfObj.end(), grid[temp1][temp2].begin(), grid[temp1][temp2].end());

		listOfObj.insert(listOfObj.end(), grid[j][k].begin(), grid[j][k].end());
	}

	return listOfObj;
}


template <class T>
void UniformGrid<T>::insert_objs_to_grid(std::vector<T*> objs)
{
	//iterate through the lines and find the right grid to insert it into
	for (int i = 0; i < objs.size(); i++) {
		//find which grid the first point of the line belongs to.
		int xcoord = objs[i]->getP1().getX();
		int j = xcoord / 1250;
		int ycoord = objs[i]->getP1().getY();
		int k = ycoord / 1250;

		//cout << "j and k are " << j << ", " << k << endl;

		//Line* temp = objs[i];

		//std::pair<int, int> * temp1 = &(temp->getP1().grid_location);
		//std::pair<int, int> * temp2 = &(temp->getP2().grid_location);

		//temp1->first = j;
		//temp1->second = k;

		//temp->getP1().grid_location.second = k;
		//temp->getP1()).grid_location.first = j;
		//temp->getP1()).grid_location.second = k;

		grid[j][k].push_back(objs[i]);
		num_of_elements++;

		//find which grid the second point of the line belongs to
		int xcoord2 = objs[i]->getP2().getX();
		int j2 = xcoord2 / 1250;
		int ycoord2 = objs[i]->getP2().getY();
		int k2 = ycoord2 / 1250;

		//cout << "j2 and k2 are " << j2 << ", " << k2 << endl;

		//temp2->first = j2;
		//temp2->second = k2;

		//temp->getP2().grid_location.first = j;
		//temp->getP2().grid_location.second = k;

		//if points belong to same column but different rows
		if (j2 == j && k2 != k) {
			grid[j2][k2].push_back(objs[i]);
			num_of_elements++;
		}
		//if points belong to same row but different column
		else if (j2 != j && k2 == k) {
			grid[j2][k2].push_back(objs[i]);
			num_of_elements++;
		}
		//if points belong to different rows and different columns
		else if (j2 != j && k2 != k) {
			grid[j2][k2].push_back(objs[i]);
			num_of_elements;
		}
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

template <class T>
std::vector<T*> UniformGrid<T>::retrieve_objs_in_grid(std::vector<T*>& listOfObj, T * obj)
{
	if (num_of_elements == 0) return listOfObj;
	//first find the cell that the obj belongs to on the grid
	int xcoord = obj->getP1().getX();
	int j = xcoord / 1250;
	int ycoord = obj->getP1().getY();
	int k = ycoord / 1250;

	//cout << "j and k are " << j << ", " << k << endl;

	listOfObj.insert(listOfObj.end(), grid[j][k].begin(), grid[j][k].end());

	//do the same thing for the second point of line
	int xcoord2 = obj->getP2().getX();
	int j2 = xcoord2 / 1250;
	int ycoord2 = obj->getP2().getY();
	int k2 = ycoord2 / 1250;

	//cout << "j2 and k2 are " << j2 << ", " << k2 << endl;

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

template <class T>
void UniformGrid<T>::clear()
{
	//iterate through the 2D array and clear all the vectors
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			grid[i][j].clear();

		}
	}
	num_of_elements = 0;
}


