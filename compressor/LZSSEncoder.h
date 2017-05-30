#pragma once
#include "BitsIO.h"
#include "Defs.h"
#include <string>
#include <fstream>
#include <set>
#include<vector>
using namespace std;
class LZSSEncoder
{
	int lookaheadptr;
	int searchptr;
	int bitswritten;
	ifstream input;
	BitsIO output;
	string file;
	set<struct data, comp> tree;
	struct data *nodes;
	vector<int>flags;
	vector<int>mostrecentoffsets;
#ifdef _DEBUG
	ofstream mydbg;
#endif
	
public:
	LZSSEncoder(string inputfilename, string outputfilename);
	int Encode();
	~LZSSEncoder();
	void outflags();
};

