#include <bits/stdc++.h>
using namespace std;
#include "QueryTimePredictor.h"

#ifndef ModelVM_H
#define ModelVM_H

class QueryTimePredictor;
class ModelVM
{
	vector<ModelQuery> queries;
	VMType type;
	public:
		ModelVM(VMType type);
		void addQuery(ModelQuery mq);
		void addQueries(std::vector<ModelQuery> toAdd);
		vector<ModelQuery> getQueries();
		bool popQuery();
		VMType getType();
		int getProvisionTime();
		int getBootTime();
		int getCostForTime(int time);
		int getCostForQuery(QueryTimePredictor* qtp, ModelQuery q);
		int getCostForQueries(QueryTimePredictor* qtp);
};

#endif