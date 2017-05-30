#pragma once
#include <fstream>
#include<algorithm>
#include<bitset>
#include<limits>
#include <string>

using namespace std;

#define IN 0
#define OUT 1
//const std::size_t BITS_PER_BYTE = std::numeric_limits<unsigned char>::digits;
//using bits_in_byte = std::bitset<BITS_PER_BYTE>;
class BitsIO
{
	string& mystring;
	int idx;
	int idy;
	int loc;
	char byte;
	bool flag;
public:
	BitsIO(string& string);
	int readbits(int y);
	void writebits(int out, int size);
	void putSymbol(int c);
	int getSymbol();
	~BitsIO();
};

