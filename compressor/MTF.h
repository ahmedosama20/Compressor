#pragma once
#include<fstream>
#include<vector>
#include "Defs.h"
using namespace std;
class MTF
{ 
	string Symbols;
public:
	MTF();
	vector<int> MTF::convertTOBijective(long long int num);
	void moveToFront(string l, vector<int>& final);
	
	string getSymbols();
	~MTF();
};

