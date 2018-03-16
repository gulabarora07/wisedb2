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

double perVMpenalty = 0;
double startupCost = 0;

/*
	Astar set implementation
*/ 
void Astar(vertex & start, vertex & goal,
	unordered_map<vertex, vertex> & came_from,
	unordered_map<vertex, cost_t> & cost_so_far,
	cost_t (*heuristic)(const vertex & a, const vertex & b) = &(Graph::heuristic),
	const bool print_on = false)
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

/*
	read penalty parameters also, name of every query should be different
*/

int main(){
	int n;
	cin>>n>>perVMpenalty>>startupCost;
	vector<query> q(n);
	for(int i = 0; i < n; i++)
		cin>>q[i];
	int t = 1;
	int start_s=clock();
	// the code you wish to time goes here
	while(t--){
		vertex st(q), goal;
		unordered_map<vertex, vertex, std::hash<vertex> > came_from;
		unordered_map<vertex, cost_t> cost_so_far;
		//	testing dijkstra
		// cout<<"Dijkstra results:"<<endl<<endl;
		// dijkstra(st,goal,came_from,cost_so_far);
		vertex u = goal;
		stringstream ss;
		stack<string> s;
		// while(u!=st){
		// 	vertex v = came_from[u];
		// 	difference(ss,v,u);
		// 	s.push(ss.str());
		// 	ss.str("");
		// 	u = v;
		// }
		// while(!s.empty()){
		// 	cout<<s.top()<<endl;
		// 	s.pop();
		// }
		// testing Astar
		cout<<"Astar results:"<<endl<<endl;
		Astar(st,goal,came_from,cost_so_far,&(Graph::heuristic),true);
		u = goal;
		while(u!=st){
			vertex v = came_from[u];
			difference(ss,v,u);
			s.push(ss.str());
			ss.str("");
			u = v;
		}
		while(!s.empty()){
			cout<<s.top()<<endl;
			s.pop();
		}
	}
	int stop_s=clock();
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
}

/*
some testing inputs:
5 5 1 
a 2 2
b 3 1
c 4 1
d 2.5 1
e 4 1

3 3 5
a 2 b 2 c 1

15 10 10
a 2.34 b 3.1 c 4.15 d 7.1 e 4.25 f 6.42 g 4.15 h 7.145 i 5.1 j 8.14 k 3.14 l 4.15 m 7.15 n 4.12 o 1.3
*/