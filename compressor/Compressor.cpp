#include "Compressor.h"
#include<cstring>


void Compressor::Compress(string inputfilename, string outputfilename, int* outuncomp, int* outcomp )
{

	/////////////read input ////////////////
	ifstream inputfile(inputfilename, ios::binary);
	inputfile.seekg(0, ios::end);
	int size = inputfile.tellg();
	string x;
	x.reserve(size);
	inputfile.seekg(0);
	x.assign(istreambuf_iterator<char>(inputfile), istreambuf_iterator<char>());
	inputfile.close();
	//////////////////////////////////////////////

	int uncompsize = x.size();

	//x = "test string";
	///////////////////////////////BWT/////////////////////////////
	string y;
	int i;
	BWT(x, y, i);
	///////////////////////////////////////////////////////////////

	///////////////////////MTF/////////////////////////
	string z;
	vector<int> result;
	MTF mtf;
	mtf.moveToFront(y, result);
	string symbols = mtf.getSymbols();
	/////////////////////////////////////////////////////

	////////////////////// AAC //////////////////////////
	string aacenoutput;
	AACEncoder* aacen = new AACEncoder(result, aacenoutput, symbols.size() + BIJECTIVEBASE - 1);
	(*aacen)();
	delete aacen;
	/////////////////////////////////////////////////////


	/////////////////////Generate final file//////////////////
	//cout << aacenoutput.size() << endl;
	//cout << symbols << endl << endl;
	ofstream outputfile2(outputfilename, ios::binary);
	string symout;
	this->symbolToBits(symbols, symout);
	BitsIO the(symout);
	the.writebits(i, 24);
	int compsize = symout.size() + aacenoutput.size();
	outputfile2 << symout << aacenoutput;
	outputfile2.close();
	//////////////////////////////////////////////////////////

	if (outuncomp != NULL)
		*outuncomp = uncompsize;

	if (outcomp != NULL)
		*outcomp = compsize;
}

void Compressor::Decompress(string inputfilename, string outputfilename)
{
	string aacenoutput, symbols; int i;
	////////
	ifstream inputfile(inputfilename, ios::binary);
	inputfile.seekg(0, ios::end);
	int size = inputfile.tellg();
	string x;
	x.reserve(size);
	inputfile.seekg(0);
	x.assign(istreambuf_iterator<char>(inputfile), istreambuf_iterator<char>());
	inputfile.close();
	/////
	symbols=bitstosymbol(x);
	BitsIO the(x);
	i = the.readbits(24);
	aacenoutput = x;
	sort(symbols.begin(), symbols.end());
	//cout << symbols << endl;
	///////////////////////Inverse AAC////////////////////////
	vector<int> aacdecoutput;
	AACDecoder* aacdec = new AACDecoder(aacenoutput, aacdecoutput, symbols.size() + BIJECTIVEBASE - 1);
	(*aacdec)();
	delete aacdec;
	///////////////////////////////////////////////////////////

	////////////////////////Inverse MTF///////////////////////
	InverseMTF imtf;
	string inverseimtf = imtf.inverseMoveToFront(aacdecoutput, symbols);
	////////////////////////////////////////////////////////////////////

	//////////////////////////Inverse BWT//////////////////////////
	string z;
	InverseBWT(inverseimtf, z, i);
	//////////////////////////////////////////////////////////////

	ofstream outputfile(outputfilename, ios::binary);
	outputfile << z;
	outputfile.close();
}
void Compressor::symbolToBits(string symbol, string& file)
{
	
	 short arr[16];
	 BitsIO out(file);
	memset(arr, 0, sizeof(arr));
	short  rang = 0;
	for (int i = 0; i < symbol.length(); ++i)
	{
		int x = (unsigned char)symbol[i];
		int idx = x / 16;
		int tmod = x % 16;
		arr[idx] |= (1 << tmod);
		rang |= (1 << idx);
	}
	//cout << rang << endl;
	out.writebits(rang, 16); 
	int k = 0;
	for (int i = 0; i < 16; i++)
	{
		if (arr[i])
		{
			out.writebits(arr[i], 16);
			//cout << (unsigned short)arr[i] << endl;
		}
	}

}
string Compressor::bitstosymbol(string& inputfile)
{
	short rang = 0;

	BitsIO in(inputfile);
	rang = in.readbits(16);
	//cout << rang <<endl; 
	int counter = 0;
	int arr[17];
	int idx = 0;
	for (int i = 0; i < 16; ++i)
	{
		if (rang&(1 << i))
		{

			arr[counter++] = i;
		}
	}
	string symbols = "";
	char x;
	short input;
	for (int i = 0; i < counter; ++i)
	{
		int ref = arr[i];
		int temp = 2;
	
		input = in.readbits(16);
			
			for (int j = 0; j < 16; ++j)
			{
				if (input&(1 << j))
				{
					char c = ref * 16 + j;
					symbols += c;
				}
			
			}
		
	}

	return symbols;

}

Compressor::Compressor()
{
}


Compressor::~Compressor()
{
}
