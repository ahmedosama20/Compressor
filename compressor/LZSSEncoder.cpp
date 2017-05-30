/*#include "LZSSEncoder.h"


#include <string>

using namespace std;


LZSSEncoder::LZSSEncoder(string inputfilename, string outputfilename) : output(outputfilename, OUT)
{
	bitswritten = 0;
	input.open(inputfilename, ios::binary);
	input.seekg(0, std::ios::end);
	int size = input.tellg();
	file.reserve(size);
	input.seekg(0);
	file.assign((std::istreambuf_iterator<char>(input)),
		std::istreambuf_iterator<char>());
	
	nodes = new struct data[size];
	for (int i = 0; i < file.size(); i++)
	{
		nodes[i] = { file.substr(i, (1 << LENGTHSIZE) + MINMATCH - 1), i };
	}
	lookaheadptr = 0;
	searchptr = -(1 << OFFSETSIZE);

#ifdef _DEBUG
	//mydbg.open("debug.txt", ios::binary);
	//mydbg << file;
	//mydbg.close();
#endif


}
void LZSSEncoder::outflags()
{
	std::ofstream o("flags.txt");
	for (int i = 0; i < flags.size(); ++i)
		o << flags[i] << endl;
	o.close();
}
int LZSSEncoder::Encode()
{
	while (lookaheadptr < file.size())
	{
		int shift = 1;
		bool increasing = true;
		int matchlength = 0;
		int position = 0;
		set<struct data, comp>::iterator it = tree.lower_bound(nodes[lookaheadptr]);
		if (tree.size() > 0)
		{
			int compares = 0;
			if (it == tree.end()) { it--;  compares++; }
			for (; (it != tree.end()) && compares < 2; it--)
			{
				string data = (*it).str;
				int itposition = (*it).position;
				int itmatchlength = 0;
				for (int i = 0; i < nodes[lookaheadptr].str.size(); i++)
				{
					if (data[i] == nodes[lookaheadptr].str[i]) itmatchlength++; else break;
				}

				if (itmatchlength > matchlength)
				{
					matchlength = itmatchlength;
					position = itposition;
				}
				else if (itmatchlength == matchlength)
				{
					if (itposition > position) position = itposition;
				}
				else if (itmatchlength < matchlength)
				{
					break;
				}
					
				if (!shortestOffset)
				{
					compares++;
				}
			}
		}
			if (matchlength < MINMATCH)
			{
				output.writebits(SYMBOL, 1);

				output.writebits(nodes[lookaheadptr].str[0], 8);
				bitswritten += 9;
#ifdef _DEBUG
				//mydbg << SYMBOL << " " << lookaheadbuffer[0] << " ";
#endif
				if (searchptr >= 0)
				{
					tree.erase(nodes[searchptr]);	
				}
				searchptr++;

				if(lookaheadptr < file.size())
				{ 
					tree.insert(nodes[lookaheadptr]);
				}
					lookaheadptr++;
			}
			else
			{
#ifdef _DEBUG
				//if (matchlength > (1<<(LENGTHSIZE - 1)))
				//{
				//	mydbg.open("lengths.txt", ios::app);
				//	mydbg << lookaheadptr - position <<  " " << matchlength << endl;
				//	mydbg.close();
				//}
#endif
				output.writebits(TOKEN, 1);

				output.writebits(lookaheadptr - position - 1, (lookaheadptr > (1 << (OFFSETSIZE-1)) ? OFFSETSIZE : (int)ceil(log2(lookaheadptr)))); // example: if offsetsize = 3 therefore searchbuffer size = 2^3 = 8 , but 3 bit values are from 0 - 7 so we minus one from the offset so it fits in 3 bits then add it when we decode
				output.writebits(matchlength - MINMATCH, LENGTHSIZE); //same thing here, if the matchlength is 8 i subtract one so it fits in 3 bits
				bitswritten += 1 + OFFSETSIZE + LENGTHSIZE;
#ifdef _DEBUG
				//mydbg << TOKEN << " " << lookaheadptr - position - 1 << " " << matchlength - 1<< " ";
#endif
				shift = searchptr + matchlength;
				while (searchptr < shift)
				{
					if (searchptr >= 0)
					{
						tree.erase(nodes[searchptr]);
					}
					searchptr++;

					if (lookaheadptr < file.size())
					{

						tree.insert(nodes[lookaheadptr]);
					}
						lookaheadptr++;
				}

			}
		
	}
	return bitswritten;

}


LZSSEncoder::~LZSSEncoder()
{
}
*/