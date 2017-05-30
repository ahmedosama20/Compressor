#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>

#include "model.h"
#include "AACEncoder.h"
#include "AACDecoder.h"
#include "BWT.h"
#include "InverseBWT.h"
#include "MTF.h"
#include "InverseMTF.h"
#include "RLEencode.h"
#include "RLEDecode.h"
#include "Defs.h"

class Compressor
{
public:
	void Compress(string inputfilename, string outputfilename, int* outuncomp = NULL, int* outcomp = NULL);
	void Decompress(string inputfilename, string outputfilename);
	Compressor();
	~Compressor();
private:
	void symbolToBits(string symbol, string& file);
	string bitstosymbol(string& inputfile);
};

