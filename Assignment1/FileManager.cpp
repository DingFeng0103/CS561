#include "FileManager.h"

FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}


int FileManager::readInput(Searcher* searcher)
{
	stringstream SSInputLine;
	ifstream ifsInputFile("input.txt");
	vector<string> vecStrElems;
	string strElem;
	int order = 0;

	string strMethod;
	getline(ifsInputFile, strMethod);
	if (0 != searcher->setMethod(strMethod))
	{
		cout << "No method found!" << endl;
		return -1;
	}

	string strStart;
	getline(ifsInputFile, strStart);
	if (0 != searcher->setStart(strStart))
	{
		cout << "No start location found!" << endl;
		return -1;
	}

	string strEnd;
	getline(ifsInputFile, strEnd);
	if (0 != searcher->setEnd(strEnd))
	{
		cout << "No end location found!" << endl;
		return -1;
	}

	string numLines;
	getline(ifsInputFile, numLines);
	if (0 != searcher->setNumLines(stoi(numLines)))
	{
		cout << "No valid number of nodes found!" << endl;
		return -1;
	}

	for (string strTmpLine; getline(ifsInputFile, strTmpLine);)
	{


		SSInputLine.str(strTmpLine);
		while (getline(SSInputLine, strElem, ' ')){
			vecStrElems.push_back(strElem);
		}

		if (vecStrElems.size() == 3)
		{
			order++;
			searcher->setNodes(vecStrElems[0], vecStrElems[1], stoi(vecStrElems[2]), order);
		}
		else if (vecStrElems.size() == 1)
		{
			if (0 != searcher->setNumTrafficEstimates(stoi(vecStrElems[0])))
			{
				cout << "Invalid number of sunday traffic estimates" << endl;
			}
		}
		else if (vecStrElems.size() == 2)
		{
			searcher->setNodes(vecStrElems[0], stoi(vecStrElems[1]));
		}
		else
		{
			cout << "Invalid input files!!" << endl;
		}

		SSInputLine.clear();
		vecStrElems.clear();

	}

	return 0;
}

int FileManager::outputResult(Searcher* searcher)
{
	Node* tmpNode = searcher->getHashTableAddr(searcher->getEnd());
	ofstream ofsOutputFile("output.txt");
	string strOutput;
	while (tmpNode->getName() != searcher->getStart())
	{
		
		strOutput.insert(0, tmpNode->getName() + ' ' + to_string(tmpNode->getCost())+'\n');
		tmpNode = tmpNode->getParent();
	}
	strOutput.insert(0, tmpNode->getName() + ' ' + to_string(tmpNode->getCost()) + '\n');

	ofsOutputFile << strOutput;
	return 0;
}