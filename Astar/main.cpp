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

double perVMpenalty = 0;
double startupCost = 0;

/*
	read penalty parameters also, name of every query should be different
*/

int main(){
	int n;
	cin>>n>>perVMpenalty>>startupCost;
	vector<query> q(n);
	unordered_map<query,int,boost::hash<query> > query_indices;
	for(int i = 0; i < n; i++){
		cin>>q[i];
		query_indices[q[i]] = i;
	}
	int t = 1;
	// int start_s=clock();
	while(t--){
		vertex st(q), goal;
		unordered_map<vertex, vertex, std::hash<vertex> > came_from;
		unordered_map<vertex, cost_t> cost_so_far;
		vertex u = goal;
		//	testing dijkstra
		// cout<<"Dijkstra results:"<<endl<<endl;
		// dijkstra(st,goal,came_from,cost_so_far);
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
		// cout<<"Astar results:"<<endl<<endl;
		Astar(st,goal,came_from,cost_so_far,&(Graph::heuristic));
		u = goal;
		vector<vertex> path;
		path.push_back(u);
		while(u!=st){
			vertex v = came_from[u];
			u = v;
			path.push_back(u);
		}

		reverse(path.begin(),path.end());

		cost_t wait_time = perVMpenalty;
		vector<int> total_of_x(n,0);
		vector<cost_t> cost_of_x(n);
		for (int i = 0; i < n; i++){
			cost_of_x[i] = q[i].cost;
		}
		vector<bool> have_x(n,false);
		int total = 0;

		auto print_features = [&](int index){
			cout<<wait_time<<endl;
			for (int i = 0; i < n; ++i){
				cout<<q[i].name<<"\t"<<(double)total_of_x[i]/(total==0?1:total)<<"\t"<<cost_of_x[i]<<"\t"<<have_x[i]<<endl;
			}
			if(index==-1)
				cout<<"Initialize VM"<<endl;
			else
				cout<<"Assign "<<q[index].name<<endl;
		};

		for(int i = 1; i < path.size(); i++){
			int index = difference(path[i-1],path[i]);
			if(index!=-1){
				index = query_indices[path[i-1].q[index]];
				total_of_x[index]++;
				wait_time+=q[index].cost;
				have_x[index] = true;
				total++;
			}
			else{
				wait_time = 0;
				total = 0;
				fill(total_of_x.begin(),total_of_x.end(),0);
				fill(have_x.begin(),have_x.end(),false);
				// fill(cost_of_x.begin(),cost_of_x.end(),0);
			}
			print_features(index);
		}
	}
	// int stop_s=clock();
	// cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
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