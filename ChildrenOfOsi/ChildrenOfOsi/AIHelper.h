#pragma once
#include "QuadTree.h"
#include "GameWindow.h"
#include "Vector2f.h"

// Visibilty graph
// Holds a map of edges (locations as keys, list of their neighbors as values)
namespace std {
	template <>
	struct hash<Vector2f> {
		inline size_t operator()(const Vector2f &location) const {
			return (hash<float>()((location.xloc)) ^ (hash<float>()(location.yloc) << 1));
		}
	};
}

struct VisibilityGraph {
	typedef typename vector<Vector2f>::iterator iter;
	unordered_map<Vector2f, vector<Vector2f>> edges;
	inline const vector<Vector2f> neighbors(Vector2f id) {
		return edges[id];
	}
	inline double cost(Vector2f from, Vector2f to) {
		return from.dist(to);
	}
};



class AIHelper
{
public:
	AIHelper();
	AIHelper(WorldObj* obj);
	~AIHelper();	
	VisibilityGraph graph;
	Vector2f start;
	Vector2f goal;
	unordered_map<Vector2f, Vector2f> came_from;
	unordered_map<Vector2f, double> cost_so_far;
	int Astar(WorldObj* obj);


private:
	//std::vector<WorldObj*> objVec;
};

