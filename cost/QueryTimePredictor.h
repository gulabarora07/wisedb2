#include <bits/stdc++.h>
// #include "temp.cpp"
#include "VMType.h"
#include "Cost.h"
#include "ModelQuery.h"
using namespace std;

#ifndef QueryTimePredictor_H
#define QueryTimePredictor_H

class ModelVM;

class QueryTimePredictor
{
  	map<int, map<VMType, int> > latencyData;
	map<int, map<VMType, int> > ioData;

	vector<int> QUERY_TYPES;
	
	vector<VMType> types;

	public:
		QueryTimePredictor(map<int, map<VMType, int> > latency, map<int, map<VMType, int> > ioData, vector<VMType> types); 
		QueryTimePredictor(vector<VMType> types);
		QueryTimePredictor();
		void loadValuesFromJSON();
		int predict(ModelQuery q, ModelVM* vm);
		int predictIO(ModelQuery q, ModelVM* vm);
		int predict(ModelQuery q, VMType vm);
		VMType getOneVM();
		void check();
};

#endif
