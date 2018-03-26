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
#define INF 1e10

/* change code to account for different costs for different machines, change vector<query> to set in vertex */
using namespace std;
typedef double cost_t;


ostream& operator<<(ostream & output, const vertex & v){
	output<<"{";
	for(int i = 0; i < v.q.size(); i++){
		output<<v.q[i];
		if(i<(int)v.q.size()-1)
			output<<", ";
	}
	return output<<"}("<<v.last_machine_no<<")";
}

int difference(ostream & output, const vertex & u, const vertex & v) throw(int){
	// output<<u<<"->"<<v<<endl;
	if(u.last_machine_no+1 == v.last_machine_no){
		// output<<"Initialize VM"<<endl;
		output<<"0"<<endl;
		return -1;
	}
	set<query> m(v.q.begin(),v.q.end());
	for(int i = 0; i < u.q.size(); i++){
		if(m.find(u.q[i])==m.end()||u.q[i].count!=v.q[i].count){
			// output<<"Assign "<<u.q[i].name<<endl;
			output<<u.q[i].name<<endl;
			return i;
		}
	}
	throw 1;
}