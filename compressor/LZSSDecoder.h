
#include "BitsIO.h"
#include "Defs.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;
class LZSSDecoder
{
	std::ofstream output;
	BitsIO input;
	string decoded;
	vector<int> mostrecentoffsets;
public:
	
	LZSSDecoder(string inputfile, string ouputfile);
	~LZSSDecoder();
	void Decode();
	string getDecoded();
};