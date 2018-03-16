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


#ifndef ALGOS_H
#define ALGOS_H

void Astar(vertex & start, vertex & goal,
	unordered_map<vertex, vertex> & came_from,
	unordered_map<vertex, cost_t> & cost_so_far,
	cost_t (*heuristic)(const vertex & a, const vertex & b) = &(Graph::heuristic),
	const bool print_on = false);

void dijkstra(vertex & start, vertex & goal,
	unordered_map<vertex, vertex> & came_from,
	unordered_map<vertex, cost_t> & cost_so_far,
	const bool print_on = false);
#endif