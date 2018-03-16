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
#define INF 1e10

/* change code to account for different costs for different machines, change vector<query> to set in vertex */
using namespace std;
typedef double cost_t;

/*
	dijkstra set implementation
*/
void dijkstra(vertex & start, vertex & goal,
	unordered_map<vertex, vertex> & came_from,
	unordered_map<vertex, cost_t> & cost_so_far,
	const bool print_on = false)
{
	set<pair<cost_t,vertex> > frontier;
	vector<vertex> neighbours;

	frontier.insert(make_pair(cost_t(0), start));
	came_from[start] = start;
	cost_so_far[start] = cost_t(0);
	if(print_on) cout<<"Start is "<<start<<" and Goal is "<<goal<<endl;

	while (!frontier.empty()) {
		vertex current = frontier.begin()->second;
		frontier.erase(frontier.begin());

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
			
			if (new_cost < cost_so_far[next]) {
				frontier.erase(make_pair(cost_so_far[next], next));
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				frontier.insert(make_pair(cost_so_far[next], next));
			}
		}
		if(print_on) cout<<endl;
	}
}