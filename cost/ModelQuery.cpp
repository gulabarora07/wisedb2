#include <bits/stdc++.h>
using namespace std;
#include "ModelQuery.h"

ModelQuery::ModelQuery(int type) {
	this->type = type;
	count++;
}

int ModelQuery::getType() {
	return type;
}