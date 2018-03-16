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
#define INF 1e10

/* change code to account for different costs for different machines, change vector<query> to set in vertex */
using namespace std;
typedef double cost_t;

#ifndef GRAPH_H
#define GRAPH_H

extern double perVMpenalty;
extern double startupCost;

class Graph{
public:
	static cost_t heuristic(const vertex & a, const vertex & b);
	static void get_neighbours(const vertex & a, vector<vertex> & neighbors);

	// return correct cost difference only if b is forward neighbour of a
	static cost_t cost_difference(const vertex & a, const vertex & b);
};

#endif