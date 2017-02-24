#include "stdafx.h"
#include "AIHelper.h"


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

AIHelper::AIHelper(WorldObj* obj)
{
}

AIHelper::~AIHelper()
{
}

inline double heuristic(Vector2f start, Vector2f goal) {
	return ((double)start.dist(goal));
}

//template<typename G>
int AIHelper::Astar(WorldObj* obj)// VisibilityGraph graph, Vector2f start, Vector2f goal, unordered_map<Vector2f, Vector2f> came_from, unordered_map<Vector2f, double> cost_so_far)
{
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

		if (current == goal) {
			break;
		}

		for (Vector2f next : graph.neighbors(current)) {
			double cost = cost_so_far[current] + graph.cost(current, next);
			if (!cost_so_far.count(next) || cost < cost_so_far[next]) {
				cost_so_far[next] = cost;
				double priority = cost + heuristic(next, goal);
				frontier.emplace(priority, next);
				came_from[next] = current;
			}
		}
	}

	return 0;

}
/* When using std::unordered_map<T>, we need to have std::hash<T> or
// provide a custom hash function in the constructor to unordered_map.
// Since I'm using std::unordered_map<tuple<int,int>> I'm defining the
// hash function here. It would be nice if C++ automatically provided
// the hash function for tuple and pair, like Python does. It would
// also be nice if C++ provided something like boost::hash_combine. In
// any case, here's a simple hash function that combines x and y:
namespace std {
	template <>
	struct hash<tuple<int, int> > {
		inline size_t operator()(const tuple<int, int>& location) const {
			int x, y;
			tie(x, y) = location;
			return x * 1812433253 + y;
		}
	};
}


/*template<typename T, typename priority_t>
struct PriorityQueue {
  typedef pair<priority_t, T> PQElement;
  priority_queue<PQElement, vector<PQElement>, 
                 std::greater<PQElement>> elements;

  inline bool empty() const { return elements.empty(); }

  inline void put(T item, priority_t priority) {
    elements.emplace(priority, item);
  }

  inline T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};*/
/*template<typename Graph>
void a_star_search
(const Graph& graph,
	typename Graph::Location start,
	typename Graph::Location goal,
	unordered_map<typename Graph::Location, typename Graph::Location>& came_from,
	unordered_map<typename Graph::Location, double>& cost_so_far)
{
	typedef typename Graph::Location Location;
	PriorityQueue<Location, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		auto current = frontier.get();

		if (current == goal) {
			break;
		}

		for (auto next : graph.neighbors(current)) {
			double new_cost = cost_so_far[current] + graph.cost(current, next);
			if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				double priority = new_cost + heuristic(next, goal);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
	}
}*/



/*
using std::unordered_map;
using std::unordered_set;
using std::array;
using std::vector;
using std::queue;
using std::priority_queue;
using std::pair;
using std::tuple;
using std::tie;
using std::string;
*/

/*template<typename L>
struct SimpleGraph {
	typedef L Location;
	typedef typename vector<Location>::iterator iterator;
	unordered_map<Location, vector<Location> > edges;

	inline const vector<Location>  neighbors(Location id) {
		return edges[id];
	}
};*/

/*SimpleGraph<char> example_graph{ {
	{ 'A',{ 'B' } },
	{ 'B',{ 'A', 'C', 'D' } },
	{ 'C',{ 'A' } },
	{ 'D',{ 'E', 'A' } },
	{ 'E',{ 'B' } }
	} };
*/




