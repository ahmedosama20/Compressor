/*#include"LZSSDecoder.h"
#include<iostream>
using namespace std;
LZSSDecoder::LZSSDecoder(string inputfile, string outputfile) :input(inputfile,IN)
{
	output.open(outputfile, ios::binary);
	decoded = "";

}
void LZSSDecoder::Decode()
{
	
	char c;
	long long int off = 0;
	long long int len = 0;
	while (1)
	{
		int flag = input.readbits(1);
		//output << flag << endl;
		if (flag == 256)
		{
			
			//cout << "out" << endl;
			break;
		}
		if (flag == (int)TOKEN)
		{
			//cout << "here" << endl;
			off = input.readbits((decoded.size() > (1 << (OFFSETSIZE - 1)) ? OFFSETSIZE : (int)ceil(log2(decoded.size()))));

			if (mostrecentoffsets.size() > 4)
				mostrecentoffsets.erase(mostrecentoffsets.begin());
			mostrecentoffsets.push_back(off);

			len = input.readbits((int)LENGTHSIZE);

			off++;
			len+= MINMATCH;
			int counter = 0;
			string extra = "";
			int i = decoded.length() - off;
			if (i < 0)
			{
				
				cout << "ok";
			}
			for (; counter < len; ++counter)
			{

				extra += decoded[i];
				++i;
				if (i == decoded.length())
				{

					//cout << "2ywa" << endl;
					decoded += extra;
					extra = "";
					i = decoded.length() - off;
				}
			}
			if (extra != "")
			{
				decoded += extra;
			}


		}

		else if (flag==(int)SYMBOL)
		
		{

			int x = input.readbits(8);
			if (x > 0xff)
			{
				cout << "nono";
			}
			c = char(x);
			decoded += c;

		}
		
	}

	
	decoded.erase(decoded.length() - 1);
	output << decoded;
}
LZSSDecoder::~LZSSDecoder()
{
	output.close();
}*/