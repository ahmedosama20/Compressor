#include "BitsIO.h"
#include<iostream>
using namespace std;

//out = true, in = false
BitsIO::BitsIO(string &string) :mystring(string)
{
	idx = 7;
	idy = -1;
	byte = 0;
	loc = 0;
}

int BitsIO::readbits(int y)
{
	//while (file.get(c)) // read byte by byte
	//bitstring += bits_in_byte(unsigned char(c)).to_string();
	//std::ifstream file(decoded, std::ios::binary);

	//long long int retval=0;
	int value = 0;
	for (int i = y - 1; i >= 0; --i)
	{
		if (idy<0)
		{
			if (loc < mystring.size())
			{
				byte = mystring[loc];
				mystring.erase(mystring.begin(), mystring.begin() + 1);
				//tempfile << byte;


				idy = 7;
			}
			else
			{

				return 258;
			}
		}

		value |= (((byte&(1 << idy)) >> idy) << (i));
		idy--;

	}
	return value;
	/*while (y--)
	{
	if (idy == -1)
	{
	if (!(input >> byte))
	{
	cout << "here" << endl;
	return -1;
	}

	idy = 7;
	}
	retval |= ((byte & (1 << idy)) >> idy) <<( y );
	idy--;
	}*/
	//return retval;
}

void BitsIO::writebits(int out, int size)
{


	for (int i = size - 1; i >= 0; --i)
	{
		byte |= (((out&(1 << i)) >> i) << idx);
		idx--;

		if (idx <0)
		{

			mystring += byte;
			/*string ss = "";
			for (int i = 7; i >= 0; --i)
			{
			char tt = ((byte&(1 << i)) >> i) + '0';
			ss += tt;
			}
			filestream << ss << endl;*/

			byte = 0;
			idx = 7;
		}
	}
}

void BitsIO::putSymbol(int c)
{
	writebits(c, 8);
}

int BitsIO::getSymbol()
{
	return readbits(8);
}


BitsIO::~BitsIO()
{
	if (idx < 7)
	{

		for (int i = idx; i >= 0; --i)
		{
			byte &= ~(1 << i);

		}
		mystring += byte;
	}

}

