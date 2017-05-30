#pragma once
#include <string>

using namespace std;

class RLEDecode
{
	int minmatch;
	string& my_in;
	string& my_out;
public:
	RLEDecode(string& in, string& out, int m);
	~RLEDecode();
};

