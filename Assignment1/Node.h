#ifndef __NODE__
#define __NODE__

#include<vector>
#include<string>
#include<iostream>
#include"Path.h"

#define UNEXPLORED 0
#define EXPLORED 1

using namespace std;

class Node
{
private:
	Node* ptrParentNode;
	int PathOrder;
	string Name;
	int State;
	int TotalCost;
	int TrafficEstimate;
	vector<Path> vecPaths;
	Node* nextChain;
public:
	Node();
	~Node();

	int setState(int state);
	int setTrafficeEstimate(int traffic_estimate);
	int setName(string name);
	int setCost(int cost);
	int setParent(Node* nodeParent);
	int addPath(string start, string end,int order, int cost);
	int setPathOrder(int order);
	int setNextChain(Node* ptrNextChain);

	int getPathOrder();
	int getEstimate();
	int getCost();
	int getState();
	int getNumPaths();
	Path* getPaths(int index);
	Node* getNextChain();
	Node* getParent();
	string getName();

};



#endif
