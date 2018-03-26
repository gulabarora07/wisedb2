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
#define INF 1e10
#ifndef VERTEX_H
#define VERTEX_H

/* change code to account for different costs for different machines, change vector<query> to set in vertex */
using namespace std;
typedef double cost_t;

/*
	class vertex
	//vector<query> is fast compared to set<query>
*/
class vertex{
public:
	vector<query> q;
	int last_machine_no;
	double last_machine_time;
	vertex():last_machine_no(0),last_machine_time(0){}
	vertex(vector<query> & a):q(a),last_machine_no(0),last_machine_time(0){}
	// copy constructor
	vertex(const vertex & other):q(other.q),last_machine_no(other.last_machine_no),last_machine_time(other.last_machine_time){}
	// copy assignment operator
	const vertex & operator=(const vertex & other){
		if(this!=&other){
			this->q = other.q;
			this->last_machine_no = other.last_machine_no;
			this->last_machine_time = other.last_machine_time;
		}
		return *this;
	}
	inline bool same_queries(const vertex & other) const {
		return this->q == other.q;
	}
	// bool comparison = result of comparing 'this' to 'other' on basis of only remaining queries
	inline bool operator==(const vertex & other) const {
		return (this->q == other.q) && (this->last_machine_no == other.last_machine_no);
	}
	inline bool operator!=(const vertex & other) const {
		return !this->operator==(other);
	}
	// required for set
	inline bool operator<(const vertex & other) const {
		return (this->last_machine_no < other.last_machine_no)||(this->q.size() < other.q.size());
	}
private:
	friend int difference(ostream &, const vertex &, const vertex &) throw(int);
	friend ostream& operator<<(ostream &, const vertex &);
};

namespace std {
	// accounts for the remaining queries and last_machine_no, part of std, therefore can be called by std::hash<vertex>()
	template <>
	struct hash<vertex>
	{
		inline size_t operator()(const vertex & x) const{
			boost::hash<int> hasher;
			size_t seed = hasher(x.last_machine_no);
			boost::hash_range(seed, x.q.begin(), x.q.end());
			return seed;
		}
	};
}

#endif