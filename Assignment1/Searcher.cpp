#include "Searcher.h"


Searcher::Searcher()
{
}


Searcher::~Searcher()
{
}

int Searcher::setMethod(string method)
{
	if (!method.empty())
	{
		this->strMethod = method;
	}
	else
	{
		cout << "No Method set!" << endl;
		return 1;
	}
	return 0;
}
int Searcher::setStart(string start)
{
	if (!start.empty())
	{
		this->strStart = start;
	}
	else
	{
		cout << "No start location set!" << endl;
		return 1;
	}

	return 0;
}
int Searcher::setEnd(string end)
{
	if (!end.empty())
	{
		this->strEnd = end;
	}
	else
	{
		cout << "No end location set!" << endl;
		return 1;
	}

	return 0;
}

int Searcher::setNumLines(int numLines)
{
	if (numLines > 0)
	{
		this->numLines = numLines;
		this->initVecNodes();
	}
	else
	{
		cout << "Invalid number of nodes !" << endl;
		return -1;
	}

	return 0;
}

int Searcher::setNumTrafficEstimates(int numTrafficEstimates)
{
	if (numTrafficEstimates > 0)
	{
		this->numTrafficEstimates = numTrafficEstimates;
	}
	else
	{
		cout << "Invalid number of nodes !" << endl;
		return -1;
	}

	return 0;
}

int Searcher::initVecNodes()
{
	if (this->getNumLines() == 0)
	{
		cout << "Can't initial nodes vector, number of nodes is 0 for now" << endl;
		return -1;
	}

	this->vecNodes.resize(2 * this->getNumLines());
	return 0;
}

string Searcher::getMethod()
{
	if (this->strMethod.empty()){
		cout << "No method has been set" << endl;
	}
	return this->strMethod;

}

string Searcher::getStart()
{
	if (this->strStart.empty()){
		cout << "No start location has been set" << endl;
	}
	return this->strStart;

}

string Searcher::getEnd()
{
	if (this->strEnd.empty()){
		cout << "No end location has been set" << endl;
	}
	return this->strEnd;
}

int Searcher::getNumLines()
{
	if (this->numLines <= 0){
		cout << "No valid number of nodes has been set" << endl;
	}
	return this->numLines;
}

Node* Searcher::getHashTableAddr(string name)
{
	std::hash<std::string> str_hash;
	int iHashIndex = str_hash(name) % (2 * this->getNumLines());

	vector<Node>::iterator tmpIterator = this->vecNodes.begin();
	advance(tmpIterator, iHashIndex);

	Node* tmpPtrNode = &(*tmpIterator);
	Node* tmpPtrNextChain = NULL;
	if (tmpPtrNode->getName().empty())
	{
		tmpPtrNode->setName(name);
		return &(*tmpPtrNode);
	}
	else if (tmpPtrNode->getName() == name)
	{
		return &(*tmpPtrNode);
	}
	while (tmpPtrNode->getNextChain() != NULL&&tmpPtrNode->getName() != name)
	{
		tmpPtrNode = tmpPtrNode->getNextChain();
	}
	if (tmpPtrNode->getName() == name){
		return tmpPtrNode;
	}
	else{
		tmpPtrNextChain = new Node;
		tmpPtrNextChain->setName(name);
		tmpPtrNode->setNextChain(tmpPtrNextChain);
		return tmpPtrNextChain;

	}

}

int Searcher::setNodes(string strAddA, string strAddB, int cost, int order)
{
	Node* tmpPtrNode = this->getHashTableAddr(strAddA);
	this->getHashTableAddr(strAddB);
	tmpPtrNode->addPath(strAddA, strAddB, order, cost);

	return 0;
}

int Searcher::setNodes(string strAddA, int traffic_estimate)
{
	Node* tmpPtrNode = this->getHashTableAddr(strAddA);

	tmpPtrNode->setTrafficeEstimate(traffic_estimate);

	return 0;
}

int Searcher::BFS()
{
	queue<Path*> vecPathFrontier;
	string strStart = this->getStart();

	Node* tmpExploringNode = this->getHashTableAddr(strStart);
	Node* ptrParentNode = NULL;
	Node* ptrChildNode = NULL;
	Path* tmpExploringPath = NULL;
	tmpExploringNode->setState(EXPLORED);
	tmpExploringNode->setCost(0);
	while (tmpExploringNode->getName() != this->getEnd())
	{
		for (int i = 0; i < tmpExploringNode->getNumPaths(); i++)
		{
			ptrChildNode = this->getHashTableAddr(tmpExploringNode->getPaths(i)->strEnd);
			if (ptrChildNode->getState() == UNEXPLORED)
			{
				ptrChildNode->setState(EXPLORED);
				vecPathFrontier.push(tmpExploringNode->getPaths(i));
			}
		}

		if (vecPathFrontier.size() != 0){
			tmpExploringPath = &(*vecPathFrontier.front());
			vecPathFrontier.pop();
			tmpExploringNode = this->getHashTableAddr(tmpExploringPath->strEnd);
		}
		else{
			cout << "All paths have been explored" << endl;
			return -1;
		}

		ptrParentNode = this->getHashTableAddr(tmpExploringPath->strStart);
		tmpExploringNode->setParent(ptrParentNode);
		tmpExploringNode->setState(EXPLORED);
		tmpExploringNode->setCost(ptrParentNode->getCost() + 1);


	}

	return 0;
}

int Searcher::DFS()
{
	stack<Path*> vecPathFrontier;
	string strStart = this->getStart();

	Node* tmpExploringNode = this->getHashTableAddr(strStart);
	Node* ptrParentNode = NULL;
	Node* ptrChildNode = NULL;
	Path* tmpExploringPath = NULL;
	tmpExploringNode->setState(EXPLORED);
	tmpExploringNode->setCost(0);
	while (tmpExploringNode->getName() != this->getEnd())
	{
		for (int i = tmpExploringNode->getNumPaths() - 1; i >= 0; i--)
		{
			ptrChildNode = this->getHashTableAddr(tmpExploringNode->getPaths(i)->strEnd);
			if (ptrChildNode->getState() == UNEXPLORED)
			{
				ptrChildNode->setState(EXPLORED);
				vecPathFrontier.push(tmpExploringNode->getPaths(i));
			}
		}

		if (vecPathFrontier.size() != 0){
			tmpExploringPath = &(*vecPathFrontier.top());
			vecPathFrontier.pop();
			tmpExploringNode = this->getHashTableAddr(tmpExploringPath->strEnd);
		}
		else{
			cout << "All paths have been explored" << endl;
			return -1;
		}

		ptrParentNode = this->getHashTableAddr(tmpExploringPath->strStart);
		tmpExploringNode->setParent(ptrParentNode);
		tmpExploringNode->setState(EXPLORED);
		tmpExploringNode->setCost(ptrParentNode->getCost() + 1);


	}

	return 0;
}

int Searcher::UCS()
{
	vector<Node*> vecNodeFrontier;
	string strStart = this->getStart();
	vector<Node*>::iterator itVecNode = vecNodeFrontier.begin();

	Node* tmpExploringNode = this->getHashTableAddr(strStart);
	Node* ptrParentNode = NULL;
	Node* ptrChildNode = NULL;
	Path* tmpExploringPath = NULL;
	int tmpCost = 0;
	int pathOrder = 1;
	tmpExploringNode->setState(EXPLORED);
	tmpExploringNode->setCost(0);
	while (tmpExploringNode->getName() != this->getEnd())
	{
		for (int i = 0; i < tmpExploringNode->getNumPaths(); i++)
		{
			tmpExploringPath = tmpExploringNode->getPaths(i);
			ptrChildNode = this->getHashTableAddr(tmpExploringPath->strEnd);
			tmpCost = tmpExploringNode->getCost() + tmpExploringPath->cost;

			if (ptrChildNode->getCost() == -1)
			{
				ptrChildNode->setCost(tmpCost);
				ptrChildNode->setParent(tmpExploringNode);
				ptrChildNode->setPathOrder(pathOrder);
				pathOrder++;
				vecNodeFrontier.push_back(ptrChildNode);
			}
			else if (ptrChildNode->getCost() > tmpCost)
			{
				itVecNode = find(vecNodeFrontier.begin(), vecNodeFrontier.end(), ptrChildNode);
				if (itVecNode == vecNodeFrontier.end()){
					vecNodeFrontier.push_back(ptrChildNode);
				}
				ptrChildNode->setState(UNEXPLORED);
				ptrChildNode->setPathOrder(pathOrder);
				pathOrder++;
				ptrChildNode->setCost(tmpCost);
				ptrChildNode->setParent(tmpExploringNode);
			}
		}

		do{
			make_heap(vecNodeFrontier.begin(), vecNodeFrontier.end(), compNodeUC());
			tmpExploringNode = &(*vecNodeFrontier.front());
			pop_heap(vecNodeFrontier.begin(), vecNodeFrontier.end(), compNodeUC());
			vecNodeFrontier.pop_back();
		} while (tmpExploringNode->getState() == EXPLORED&&vecNodeFrontier.size() != 0);

		if (tmpExploringNode->getState() == EXPLORED)
		{
			cout << "All paths have been explored" << endl;
			return -1;
		}

		tmpExploringNode->setState(EXPLORED);

	}

	return 0;
}

int Searcher::A_StarSeach()
{
	vector<Node*> vecNodeFrontier;
	string strStart = this->getStart();
	vector<Node*>::iterator itVecNode = vecNodeFrontier.begin();

	Node* tmpExploringNode = this->getHashTableAddr(strStart);
	Node* ptrParentNode = NULL;
	Node* ptrChildNode = NULL;
	Path* tmpExploringPath = NULL;
	int tmpCost = 0;
	int pathOrder = 1;
	tmpExploringNode->setState(EXPLORED);
	tmpExploringNode->setCost(0);

	while (tmpExploringNode->getName() != this->getEnd())
	{

		for (int i = 0; i <tmpExploringNode->getNumPaths(); i++)
		{
			tmpExploringPath = tmpExploringNode->getPaths(i);
			ptrChildNode = this->getHashTableAddr(tmpExploringPath->strEnd);
			tmpCost = tmpExploringNode->getCost() + tmpExploringPath->cost;

			if (ptrChildNode->getCost() == -1)
			{
				ptrChildNode->setCost(tmpCost);
				ptrChildNode->setParent(tmpExploringNode);
				ptrChildNode->setPathOrder(pathOrder);
				pathOrder++;
				vecNodeFrontier.push_back(ptrChildNode);
			}
			else if (ptrChildNode->getCost() > tmpCost)
			{
				itVecNode = find(vecNodeFrontier.begin(), vecNodeFrontier.end(), ptrChildNode);
				if (itVecNode == vecNodeFrontier.end()){
					vecNodeFrontier.push_back(ptrChildNode);
				}
				ptrChildNode->setState(UNEXPLORED);
				ptrChildNode->setPathOrder(pathOrder);
				pathOrder++;
				ptrChildNode->setCost(tmpCost);
				ptrChildNode->setParent(tmpExploringNode);
			}
		}

		do{
			make_heap(vecNodeFrontier.begin(), vecNodeFrontier.end(), compNodeAStar());
			tmpExploringNode = &(*vecNodeFrontier.front());
			pop_heap(vecNodeFrontier.begin(), vecNodeFrontier.end(), compNodeAStar());
			vecNodeFrontier.pop_back();
		} while (tmpExploringNode->getState() == EXPLORED&&vecNodeFrontier.size() != 0);

		if (tmpExploringNode->getState() == EXPLORED)
		{
			cout << "All paths have been explored" << endl;
			return -1;
		}

		tmpExploringNode->setState(EXPLORED);

	}

	return 0;
}

int Searcher::getResult()
{
	if (this->getMethod() == "BFS")
	{
		return this->BFS();
	}
	else if (this->getMethod() == "DFS")
	{
		return this->DFS();
	}
	else if (this->getMethod() == "UCS")
	{
		return this->UCS();
	}
	else if (this->getMethod() == "A*")
	{
		return this->A_StarSeach();
	}

	return -1;

}