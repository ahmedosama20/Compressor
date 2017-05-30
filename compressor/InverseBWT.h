#pragma once
#include <string>
using namespace std;

class InverseBWT
{
	int size;
	int* T;
public:
	InverseBWT(string &in, string &out, int &ini);
	~InverseBWT();
};

