#include <bits/stdc++.h>
using namespace std;
#include "ModelQuery.h"

int ModelQuery::count = 0;

ModelQuery::ModelQuery(int type) {
	this->type = type;
	count++;
}

int ModelQuery::getType() {
	return type;
}