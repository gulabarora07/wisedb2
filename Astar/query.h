/*
	Author		:	Gulab Arora
	Institute	:	IIT Kharagpur
*/
#include <bits/stdc++.h>
#include <unordered_map>
#include <boost/functional/hash_fwd.hpp>
#include <boost/functional/hash.hpp>
#include <ctime>
#define INF 1e10

#ifndef QUERY_H
#define QUERY_H

/* change code to account for different costs for different machines, change vector<query> to set in vertex */
using namespace std;
typedef double cost_t;

/*
	query class(tempelate + no_of_queries)
	every query(even same cost) should have unique name
	query = tempelate(name + cost) + count
*/

class query{
private:
	friend istream& operator>>(istream &, query &);
	friend ostream& operator<<(ostream &, const query &);
	friend size_t hash_value(const query &);
public:
	string name;
	cost_t cost;
	int count;

	cost_t min_cost() const{
		return cost;
	}
	inline bool operator==(const query & other) const{
		return this->name == other.name && this->count == other.count;
	}
	inline bool operator<(const query & other) const{
		return this->name < other.name;
	}
};

inline istream& operator>>(istream & input, query & q){
	return input>>q.name>>q.cost>>q.count;
}
inline ostream& operator<<(ostream & output, const query & q){
	return output<<q.name<<"["<<q.count<<"]";
}

// part of boost, can be called by boost::hash<query>(), required by std::hash<vertex>()
inline size_t hash_value(const query & x)
{
	size_t seed = x.count;
	boost::hash<string> hasher;
	boost::hash_combine(seed,hasher(x.name));
	return seed;
}

#endif