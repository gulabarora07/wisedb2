#include <bits/stdc++.h>
// #include "temp.cpp"

#ifndef QueryTimePredictor_H
#define QueryTimePredictor_H
#include "VMType.h"
#include "Cost.h"
#include "ModelQuery.h"
#include "ModelVM.h"
using namespace std;
class ModelVM;

class QueryTimePredictor
{
  	map<int, map<VMType, int> > latencyData;
	map<int, map<VMType, int> > ioData;

	vector<int> QUERY_TYPES;
	
	vector<VMType> types;

	public:
		QueryTimePredictor(map<int, map<VMType, int> > latency, map<int, map<VMType, int> > ioData, vector<VMType> types); 
		QueryTimePredictor(vector<VMType> types,int numQ);
		QueryTimePredictor();
		void loadValuesFromJSON(int numQ);
		int predict(ModelQuery q, ModelVM* vm);
		int predictIO(ModelQuery q, ModelVM* vm);
		int predict(ModelQuery q, VMType vm);
		VMType getOneVM();
		void check();
};

#endif
