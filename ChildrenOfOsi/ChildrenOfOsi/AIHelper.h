#pragma once
#include "QuadTree.h"
#include "GameWindow.h"
#include "Vector2f.h"
#include "CheckClass.h"


class AIManager;

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
	unordered_map<Vector2f, vector<Vector2f>> edges;
	vector<Vector2f> vertices;
	vector<pair<Vector2f, Vector2f>> obstacles;
	inline const vector<Vector2f> neighbors(Vector2f id) {
		return edges[id];
	}
	inline double cost(Vector2f from, Vector2f to) {
		return from.dist(to);
	}
	int orientation(Vector2f p, Vector2f q, Vector2f r);
	bool intersect(Vector2f p1, Vector2f q1, Vector2f p2, Vector2f q2);
	void insert(Vector2f v);
	void _print();
};

class AIHelper
{
public:
	AIHelper();
	~AIHelper();	
	VisibilityGraph graph;
	Vector2f start;
	Vector2f goal;
	unordered_map<Vector2f, Vector2f> came_from;
	unordered_map<Vector2f, double> cost_so_far;
	vector<Vector2f> get_path(NPC* npc);
	int astar_search(WorldObj* obj);
	int plan_step(WorldObj* obj);
    AIManager* manager;
private:
	
	//std::vector<WorldObj*> objVec;
};

