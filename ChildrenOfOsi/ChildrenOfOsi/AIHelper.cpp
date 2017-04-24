#include "stdafx.h"
#include "AIHelper.h"
#include "AIManager.h"

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>




AIHelper::AIHelper()
{
}

AIHelper::~AIHelper()
{
}

void VisibilityGraph::_print() {
	for (Vector2f vert : vertices) {
		//std:://////cout << "{{" << vert.getXloc() << "," << vert.getYloc() << "}, {";
		for (Vector2f neighb : neighbors(vert)) {
			//std:://////cout << "{" << neighb.getXloc() << "," << neighb.getYloc() << "} ";
		}
		//std:://////cout << "}}," << std::endl;
	}
}

void VisibilityGraph::insert(Vector2f v) {
	bool visible;
	vertices.push_back(v);
	for (Vector2f next : vertices) {
		if (v == next) continue;
		visible = true;
		for (auto check : obstacles) {
			if (intersect(v, next, check.first, check.second)) {
				visible = false;
				break;
			}
		}
		if (visible) {
			edges[v].push_back(next);
			edges[next].push_back(v);
		}
	}
}

int VisibilityGraph::orientation(Vector2f p, Vector2f q, Vector2f r) {
	int val = (q.getYloc() - p.getYloc()) * (r.getXloc() - q.getXloc()) - (q.getXloc() - p.getXloc()) * (r.getYloc() - q.getYloc());
	if (val == 0) return 0; //colinear
	return (val > 0) ? 1 : 2; //clockwise or counterclockwise
}
float Area2(Vector2f a, Vector2f b, Vector2f c) {
	return (b.getXloc() - a.getXloc()) * (c.getYloc() - a.getYloc()) -
		(c.getXloc() - a.getXloc()) * (b.getYloc() - a.getYloc());
}
bool isOnLeft(Vector2f a, Vector2f b, Vector2f c) {
	return Area2(a, b, c) > 0;
}
bool isOnRight(Vector2f a, Vector2f b, Vector2f c) {
	return Area2(a, b, c) < 0;
}

bool VisibilityGraph::intersect(Vector2f p1, Vector2f q1, Vector2f p2, Vector2f q2) {
	
	if ((isOnLeft(p2, q2, p1) && isOnRight(p2, q2, q1)) || (isOnLeft(p2, q2, q1) && isOnRight(p2, q2, p1))) {
		return true;
	}
	
	/*float o1 = orientation(p1, q1, p2);
	float o2 = orientation(p1, q1, q2);
	float o3 = orientation(p2, q2, p1);
	float o4 = orientation(p2, q2, q1);

	if (o1 != o2 && o3 != o4) return false;*/

	//p2 lies on segment p1q1
	//if (o1 == 0 && onSegment(p1, p2, q1)) return true;
	//q2 lies on segment p1q1

	//p1 lies on segment p2q2

	//q1 lies on segment p2q2

	return false;
}

inline double heuristic(Vector2f start, Vector2f goal) {
	return ((double)start.dist(goal));
}

vector<Vector2f> AIHelper::get_path(NPC* obj)
{
	vector<Vector2f> path;
	Vector2f current = obj->destination;
	//path.push_back(current);
	////std:://////cout << "Push to path" << std::endl;
	////std:://////cout << "X: " << current.getXloc() << " Y: " << current.getYloc() << std::endl;
	while (!(current == start)) {
		path.push_back(current);
		//std:://////cout << "Push to path" << std::endl;
		//std:://////cout << "X: " << current.getXloc() << " Y: " << current.getYloc() << std::endl;
		current = came_from[current];
	}
	//std::reverse(path.begin(), path.end());
	path.push_back(start);
	return path;
}

//template<typename G>
int AIHelper::astar_search(WorldObj* obj)// VisibilityGraph graph, Vector2f start, Vector2f goal, unordered_map<Vector2f, Vector2f> came_from, unordered_map<Vector2f, double> cost_so_far)
{	
	bool path_exists = false;
	NPC* npc;
	if (obj->getType() >= WorldObj::TYPE_SOLDIER) {
		if (!(npc = CheckClass::isNPC(obj))) {
			LOG("Error: No movable object");
			return 1;
		}
		//vec2f dest = obj->destination;
		//container holding path returned;
		//add path and destination fields to each object
		typedef pair<double, Vector2f> element;
		priority_queue<element, vector<element>, std::greater<element>> frontier;
		frontier.emplace(0, start);

		came_from[start] = start;
		cost_so_far[start] = 0;

		while (!frontier.empty()) {
			Vector2f current = frontier.top().second;
			frontier.pop();
			//std:://////cout << "Popping" << std::endl;
			if (current == npc->destination) {
				//std:://////cout << "Found a path" << std::endl;
				path_exists = true;
				//for (auto vert : came_from) {
				//	//std:://////cout << "X: " << vert.getXloc() << " Y: " << vert.getYloc() << std::endl;
				//}
				break;
			}
			//std:://////cout << "X: " << current.getXloc() << " Y: " << current.getYloc() << std::endl;
			//std:://////cout << "Expand the neighbors!" << std::endl;
			for (Vector2f next : graph.neighbors(current)) {
				//std:://////cout << "X: " << next.getXloc() << " Y: " << next.getYloc() << std::endl;
				double cost = cost_so_far[current] + graph.cost(current, next);
				if (!cost_so_far.count(next) || cost < cost_so_far[next]) {
					cost_so_far[next] = cost;
					double priority = cost + heuristic(next, npc->destination);
					frontier.emplace(priority, next);
					came_from[next] = current;
				}
			}
		}
		if (!path_exists) {
			npc->waypoint = Vector2f(0, 0);
		}
		else {
			npc->waypoints = get_path(npc);
			npc->waypoint = npc->waypoints.back();
			came_from.clear();
			cost_so_far.clear();
		}
		//	//std:://////cout << "Done" << std::endl;
		for (int i = 0; i < came_from.size(); i++) {
			//		//std:://////cout << "X: " << came_from[i].getXloc() << " Y: " << came_from[i].getYloc() << std::endl;
		}
	}
	return 0;

}

int AIHelper::plan_step(WorldObj* obj) {
	int result;
	
	////std:://////cout << "take a step" << std::endl;

	NPC* npc;
	if (obj->getType() >= WorldObj::TYPE_SOLDIER) {
		if (!(npc = CheckClass::isNPC(obj))) {
			LOG("AIHelper:plan_step: obj not movable");
			return 1;
		}
		//npc->waypoint = npc->waypoints.back();
	//	npc->waypoints.pop_back();
		//npc->setSpeed(6.0F);
		float diffX = npc->getX() - npc->waypoint.getXloc();
		float diffY = npc->getY() - npc->waypoint.getYloc();

		float speed = npc->getSpeed();

		if (abs(diffX) < (speed*1.5)) diffX = 0;
		if (abs(diffY) < (speed*1.5)) diffY = 0;


		float slope;
		float xSpeed;
		float ySpeed;

		if (diffX == 0) {
			xSpeed = 0;
			ySpeed = speed;
		}
		else
		{
			slope = abs(diffY / diffX);
			xSpeed = speed / (slope + 1);
			ySpeed = xSpeed*slope;
		}
		


	//	float xSpeed = sqrt((speed*speed) / (slope + 1));
	//	float ySpeed = slope*xSpeed;
		npc->setDiagXSpeed(xSpeed);
		npc->setDiagYSpeed(ySpeed);
		////std:://////cout << diffX << " and " << diffY << std::endl;



		////std:://////cout << "new " << diffX << " and " << diffY << std::endl;

		//diagXSpeed = npc->getDiagXSpeed();
		//diagYSpeed = npc->getDiagYSpeed();
		if (diffX < 0) //Waypoint is to the right
		{
			if (diffY < 0) { //To the right and below
				manager->createTaskWithObj("Move_Down_Right", "MOVE", obj);
			}
			else if (diffY > 0) { //To the right and above
				manager->createTaskWithObj("Move_Up_Right", "MOVE", obj);
			}
			else //diff is 0, only move right
			{
				manager->createTaskWithObj("Move_Right", "MOVE", obj);
			}
		}
		else if (diffX > 0)  // Waypoint is to the left
		{
			if (diffY < 0) { //To the left and below
				manager->createTaskWithObj("Move_Down_Left", "MOVE", obj);
			}
			else if (diffY > 0) { //To the left and above
				manager->createTaskWithObj("Move_Up_Left", "MOVE", obj);
			}
			else //diff is 0, only move left
			{
				manager->createTaskWithObj("Move_Left", "MOVE", obj);
			}
		}
		else  //Waypoint not left or right
		{
			if (diffY < 0) //Waypoint only below
			{
				manager->createTaskWithObj("Move_Down", "MOVE", obj);
			}
			else if (diffY > 0) //Waypoint is only up
			{
				manager->createTaskWithObj("Move_Up", "MOVE", obj);
			}
			else  //Waypoint is close enough to stop
			{
		//		//std:://cout << npc->getID() << " Reached waypoint" << std::endl;
				manager->createTaskWithObj("Stop", "MOVE", obj);
				npc->setLoc(npc->waypoint);
				if (npc->waypoints.size() == 0) { //This was the final waypoint, destination reached
					//std:://////cout << npc->getName() << ": Last waypoint" << std::endl;
					npc->destination = Vector2f(0, 0); //"nullify" destination
					npc->waypoint = Vector2f(0, 0); //"nullify" waypoint
					npc->setMode(WAIT);
				}
				else //Set the obj's new waypoint to be the next in the path to destination
				{
					npc->waypoint = npc->waypoints.back();
					npc->waypoints.pop_back();
				}
			}
		}

		//	return result;
	}
	
	return 0;
}


