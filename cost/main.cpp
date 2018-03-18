#include <bits/stdc++.h>
#include "Cost.h"
#include "VMType.h"
#include "QueryTimePredictor.h"
#include "ModelVM.h"
#include "ModelQuery.h"
using namespace std;

int main()
{
	vector<VMType> v;
	// Decide which types of v you want
	for(int i=0;i<7;i++)
	{
		VMType temp1(i);
		v.push_back(temp1);
	}
	cout<<"size of v "<<v.size()<<endl;
	int numQ = 16; // Set number of queries here
	QueryTimePredictor qtp(v,numQ);
	qtp.check();	
}