#ifndef __PATH__
#define __PATH__

#include<string>
using namespace std;

class Path{
public:
	Path(string start, string end, int order, int cost);
	~Path();

	string strStart;
	string strEnd;
	int order;
	int cost;

};

#endif