#pragma once
#include "BitsIO.h"
#include "model.h"
#include <string>
#include <vector>

using namespace std;


class AACEncoder
{

public:
	int getSymbol()
	{
		if (inputindex >= m_input.size())
		{
			return nsym;
		}
		else
		{
			inputindex++;
			return m_input[inputindex - 1];
		}
	}
	AACEncoder(vector<int>& input, string& output, int numberofsymbols/*257*/)
		: m_input(input),
		m_output(output),
		m_model(numberofsymbols)
	{
		nsym = numberofsymbols;
		inputindex = 0;
	}
	int operator()()
	{

		int pending_bits = 0;
		unsigned long long int low = 0;
		unsigned long long int high = MAX;
		for (; ; ) {
			int c = getSymbol();
			//if (c == -1)
			//	c = 257;

			prob p = m_model.getProbability(c);
			unsigned long long int range = high - low + 1;
			high = low + (range * p.high / p.count) - 1;
			low = low + (range * p.low / p.count);


			for (; ; ) {
				if (high < HALF)
					putbitpluspending(0, pending_bits);
				else if (low >= HALF)
					putbitpluspending(1, pending_bits);
				else if (low >= Q1 && high < Q3) {
					pending_bits++;
					low -= Q1;
					high -= Q1;
				}
				else
					break;
				high <<= 1;
				high++;
				low <<= 1;
				high &= MAX;
				low &= MAX;
			}
			if (c == nsym)
				break;
		}
		pending_bits++;
		if (low < Q1)
			putbitpluspending(0, pending_bits);
		else
			putbitpluspending(1, pending_bits);

		return 0;
	}

	 void putbitpluspending(bool bit, int &pending_bits)
	{
		m_output.writebits(bit, 1);
		for (int i = 0; i < pending_bits; i++)
			m_output.writebits(!bit, 1);
		pending_bits = 0;
	}
private:
	BitsIO m_output;
	vector<int>& m_input;
	model m_model;
	int inputindex;
	int nsym;
};
