/*
	Author		:	Gulab Arora
	Institute	:	IIT Kharagpur
*/
#include <bits/stdc++.h>
#include <unordered_map>
#include <boost/functional/hash_fwd.hpp>
#include <boost/functional/hash.hpp>
#include <ctime>
#include "query.h"
#include "vertex.h"
#include "algos.h"
#include "graph.h"
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
	for(int _tt=0;_tt<174600;_tt++)
	{
		perVMpenalty = startupCost = 0;
		int n;
		cin>>n>>perVMpenalty>>startupCost;
		vector<query> q(n);
		unordered_map<string, int, boost::hash<string> > query_indices;
		query_indices.clear();
		for(int i = 0; i < n; i++){
			cin>>q[i];
			query_indices[q[i].name] = i;
		}
		int t = 1;
		while(t--){
			vertex st(q), goal;
			unordered_map<vertex, vertex, std::hash<vertex> > came_from;
			unordered_map<vertex, cost_t, std::hash<vertex> > cost_so_far;
			vertex u = goal;
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

			cost_t wait_time = 0;
			vector<int> total_of_x(n,0);
			vector<cost_t> cost_of_x(n);
			vector<int> remaining_queries(n);
			for (int i = 0; i < n; i++){
				cost_of_x[i] = q[i].cost;
				remaining_queries[i] = q[i].count;
			}
			vector<bool> have_x(n,false);
			int total = 0;

			auto print_features = [&]{
				cout<<wait_time<<" ";
				for (int i = 0; i < n; ++i){
					cout<<(double)total_of_x[i]/(total==0?1:total)<<" ";
					cout<<cost_of_x[i]<<" "<<have_x[i]<<" ";
					cout<<remaining_queries[i]<<endl;
				}
				cout<<endl;
			};

			for(int i = 2; i < path.size(); i++){
				print_features();
				if(remaining_queries[i] < 0)
				{
					cout<<"Test:"<<_tt<<endl;
					exit(-1);
				}
				int index = difference(cout, path[i-1], path[i]);
				if(index!=-1){
					index = query_indices[path[i-1].q[index].name];
					total_of_x[index]++;
					wait_time+=q[index].cost;
					have_x[index] = true;
					total++;
					remaining_queries[index]--;
					for(int i = 0; i < cost_of_x.size(); i++){
						if(wait_time+q[i].cost>perVMpenalty)
							cost_of_x[i] = INF;
					}
				}
				else{
					wait_time = 0;
					total = 0;
					fill(total_of_x.begin(),total_of_x.end(),0);
					for(int i = 0; i < cost_of_x.size(); i++)
						cost_of_x[i] = q[i].cost;
				}
			}
		}
	}
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