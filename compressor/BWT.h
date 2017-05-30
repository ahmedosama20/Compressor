#pragma once
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class BWT
{

	string &thein, &theout;
public:

	int size;
	BWT(string &in, string &out, int &outi);
	
	~BWT();
};


	
