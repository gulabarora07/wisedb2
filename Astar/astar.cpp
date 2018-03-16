/*
	Author		:	Gulab Arora
	Institute	:	IIT Kharagpur
*/
#include <bits/stdc++.h>
#include <unordered_map>
#include <boost/functional/hash_fwd.hpp>
#include <boost/functional/hash.hpp>
#include <ctime>
#include "vertex.h"
#include "query.h"
#include "graph.h"
#include "algos.h"
#define INF 1e10

/* change code to account for different costs for different machines, change vector<query> to set in vertex */
using namespace std;
typedef double cost_t;

/*
	Astar set implementation
*/ 
void Astar(vertex & start, vertex & goal,
	unordered_map<vertex, vertex> & came_from,
	unordered_map<vertex, cost_t> & cost_so_far,
	cost_t (*heuristic)(const vertex & a, const vertex & b),
	const bool print_on)
{
	set<pair<cost_t,vertex> > openList;
	vector<vertex> neighbours;

	openList.insert(make_pair(cost_t(0)+heuristic(start,goal), start));
	came_from[start] = start;
	cost_so_far[start] = cost_t(0);
	if(print_on) cout<<"Start is "<<start<<" and Goal is "<<goal<<endl;

	while (!openList.empty()) {
		vertex current = openList.begin()->second;
		openList.erase(openList.begin());

		if(print_on) cout<<current<<": \t";
		
		if (current.same_queries(goal)){
			goal = current;
			if(print_on) cout<<"reached goal with "<<current<<endl;
			break;
		}
		
		Graph::get_neighbours(current, neighbours);
		for (vertex next : neighbours) {
			
			if(print_on) cout<<next<<"\t";

			cost_t new_cost = cost_so_far[current] + Graph::cost_difference(current, next);
			if(cost_so_far.find(next) == cost_so_far.end())
				cost_so_far[next] = INF;
			
			cost_t h = heuristic(next,goal);
			if (new_cost < cost_so_far[next]) {
				openList.erase(make_pair(cost_so_far[next] + h, next));
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				openList.insert(make_pair(cost_so_far[next] + h, next));
			}
		}
		if(print_on) cout<<endl;
	}
}