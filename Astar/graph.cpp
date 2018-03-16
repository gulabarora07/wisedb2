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
	Graph class
	//to do
	change penalty condition in get_neighbours, add comments
*/
cost_t Graph::heuristic(const vertex & a, const vertex & b){
	set<query> m(b.q.begin(),b.q.end());
	cost_t ans = 0;
	for(int i = 0; i < a.q.size(); i++){
		if(m.find(a.q[i])==m.end())
			ans+=a.q[i].count*a.q[i].min_cost();
	}
	return ans;
}

void Graph::get_neighbours(const vertex & a, vector<vertex> & neighbors){
	neighbors.clear();
	vertex b;
	// assign new machine only when this machine has served atleast one query i.e. last_machine_time>0
	if(a.last_machine_no==0 || a.last_machine_time>0){
		vertex b = a;
		b.last_machine_no++;
		b.last_machine_time = 0;
		neighbors.push_back(b);
	}
	if(a.last_machine_no)
		for(int i = 0; i < a.q.size(); i++){
			if(a.q[i].cost+a.last_machine_time <= perVMpenalty){											/* penalty condition */
				b = a;
				b.q[i].count--;
				if(b.q[i].count==0)
					b.q.erase(b.q.begin()+i);
				b.last_machine_time+=a.q[i].cost;
				neighbors.push_back(b);
			}
		}
}

// return correct cost difference only if b is forward neighbour of a
cost_t Graph::cost_difference(const vertex & a, const vertex & b){
	// cost of a already includes a.last_machine_time, therefore, it need to be removed
	if(b.last_machine_no==a.last_machine_no+1)
		return startupCost+perVMpenalty-a.last_machine_time;
	set<query> m(b.q.begin(),b.q.end());
	cost_t ans = 0;
	for(int i = 0; i < a.q.size(); i++){
		if(m.find(a.q[i])==m.end()||a.q[i].cost!=b.q[i].cost){
			ans+=a.q[i].min_cost();
			break;
		}
	}
	return ans;
}