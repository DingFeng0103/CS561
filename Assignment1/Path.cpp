#include "Path.h"



Path::Path(string start, string end, int order, int cost)
{
	this->strStart = start;
	this->order = order;
	this->cost = cost;
	this->strEnd = end;
}

Path::~Path()
{

}