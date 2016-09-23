#ifndef __FILEMANAGER__
#define __FILEMANAGER__

#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<stack>
#include<iostream>
#include"Searcher.h"
using namespace std;

class FileManager
{
public:
	int readInput(Searcher* searcher);
	int outputResult(Searcher* searcher);
	FileManager();
	~FileManager();
};

#endif