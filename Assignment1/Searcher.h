#ifndef __SEARCHER__
#define __SEARCHER__

#include"Node.h"
#include<string>
#include<iostream>
#include<queue>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Searcher
{
private:
	string strStart;
	string strEnd;
	int numLines;
	string strMethod;
	vector<Node> vecNodes;
	int numTrafficEstimates;

public:
	Searcher();
	~Searcher();

	int initVecNodes();
	int setMethod(string method);
	int setStart(string start);
	int setEnd(string end);
	int setNumLines(int numLines);
	int setNumTrafficEstimates(int numTrafficEstimates);
	int setNodes(string strAddA, string strAddB, int cost, int order);
	int setNodes(string strAddA, int traffic_estimate);

	Node* getHashTableAddr(string name);
	string getMethod();
	string getStart();
	string getEnd();
	int getNumLines();

	struct compNodeUC {
		bool operator()(Node* const& nodeA, Node* const& nodeB) const {	
			return nodeA->getCost() == nodeB->getCost() ? nodeA->getPathOrder() > nodeB->getPathOrder():nodeA->getCost() > nodeB->getCost();
		}
	};

	struct compNodeAStar {
		bool operator()(Node* const& nodeA, Node* const& nodeB) const {
			int costA = nodeA->getCost() + nodeA->getEstimate();
			int costB = nodeB->getCost() + nodeB->getEstimate();
			
			return costA == costB ? nodeA->getPathOrder() > nodeB->getPathOrder():costA > costB;
		}
	};
	int BFS(); //Bread First Search
	int DFS();
	int UCS();
	int A_StarSeach();
	int getResult();
};

#endif