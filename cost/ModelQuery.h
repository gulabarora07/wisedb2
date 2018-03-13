#include <bits/stdc++.h>
using namespace std;

#ifndef ModelQuery_H
#define ModelQuery_H

class ModelQuery
{
	int type;
	// Should we make it atomic? Not necessary i think
	static int count;
	public:
		ModelQuery(int type);
		int getType();
};

#endif