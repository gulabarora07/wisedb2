#include <bits/stdc++.h>
using namespace std;

#include "VMType.h"

VMType::VMType(int id = 0)
{
	this->id = id;
}
int VMType::getCost() 
{
	switch(id) 
	{
		case 4:   // C4_LARGE
			return 1160;
		case 5:
			return 2320;
		case 3:
			return 1400;
		case 2:
			return 700;
		case 1:
			return 520;
		case 0:
			return 260;
		case 6:
			return 1000*60*60; // costs 1 per milisecond
		default:
			return INT_MAX;
	}
}
// int fromString(string s) {
// 	switch (s) {
// 		case "c4.large":
// 			return 4;
// 		case "c4.xlarge":
// 			return 5;
// 		case "m3.large":
// 			return 3;
// 		case "m3.medium":
// 			return 2;
// 		case "t2.medium":
// 			return 1;
// 		case "t2.small":
// 			return 0;
// 		case "unit":
// 			return 6;
// 		default:
// 			return null;
// 	}
// }

int VMType::getId()
{
	return id;
}

bool VMType::operator< (const VMType& c) const
{
	return (this->id < c.id);
}
