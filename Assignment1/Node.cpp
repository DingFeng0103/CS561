#include "Node.h"


Node::Node()
{
	this->ptrParentNode = NULL;
	this->Name.clear();
	this->PathOrder = 0;
	this->State = UNEXPLORED;
	this->TotalCost = -1;
	this->TrafficEstimate = 0;
	this->vecPaths.clear();
	this->nextChain = NULL;
}

Node::~Node()
{

}



int Node::setName(string name)
{
	this->Name = name;
	return 0;
}

int Node::setState(int state)
{
	this->State = state;
	return 0;
}

int Node::setPathOrder(int order)
{
	this->PathOrder = order;
	return 0;
}

int Node::getPathOrder()
{
	return this->PathOrder;
}

int Node::getEstimate()
{
	return this->TrafficEstimate;
}

int Node::getState()
{
	return this->State;
}

Node* Node::getNextChain()
{
	return this->nextChain;
}

string Node::getName()
{
	return this->Name;
}

int Node::getNumPaths()
{
	return this->vecPaths.size();
}

Node* Node::getParent()
{
	return this->ptrParentNode;
}

int Node::addPath(string start, string end, int order, int cost)
{
	Path *tmpPath = new Path(start, end, order, cost);
	this->vecPaths.push_back(*tmpPath);

	return 0;

}

int Node::setTrafficeEstimate(int traffic_estimate)
{
	this->TrafficEstimate = traffic_estimate;
	return 0;
}

int Node::setCost(int cost)
{
	this->TotalCost = cost;
	return 0;
}

int Node::setParent(Node* nodeParent)
{
	this->ptrParentNode = nodeParent;
	return 0;
}

int Node::getCost()
{
	return this->TotalCost;
}
Path* Node::getPaths(int index)
{
	if (index >= this->vecPaths.size())
	{
		cout << "Invalid index, exceed maximum number of path in this node" << endl;
	}

	vector<Path>::iterator tmpIterator = this->vecPaths.begin();
	advance(tmpIterator, index);

	return &(*tmpIterator);

}

int Node::setNextChain(Node* ptrNextChain)
{
	this->nextChain = ptrNextChain;
	return 0;
}
