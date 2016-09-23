#include<iostream>
#include<functional>

#include"Node.h"
#include"FileManager.h"
#include"Searcher.h"
using namespace std;
int main()
{
	FileManager fm;
	Searcher searcher;
	fm.readInput(&searcher);
	searcher.getResult();
	fm.outputResult(&searcher);

//	getchar();
}