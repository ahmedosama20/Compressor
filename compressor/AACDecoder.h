
#pragma once
#include "BitsIO.h"
#include "model.h"

#include <string>


using namespace std;
class AACDecoder
{

public:
	void putSymbol(int c)
	{
		m_output.push_back(c);
	}
	AACDecoder(string& input, vector<int>& output, int numberofsymbols)
		: m_input(input),
		m_output(output),
		m_model(numberofsymbols)
	{
		nsym = numberofsymbols;
	}
	int operator()()
	{

		unsigned long long int high = MAX;
		unsigned long long int low = 0;
		unsigned long long int value = 0;
		for (int i = 0; i < 32; i++) {
			value <<= 1;
			value += m_input.readbits(1) ? 1 : 0;
		}
		for (; ; ) {
			unsigned long long int range = high - low + 1;
			unsigned long long int scaled_value = ((value - low + 1) * m_model.getCount() - 1) / range;
			int c;
			prob p = m_model.getChar(scaled_value, c);
			if (c == nsym)
				break;
			putSymbol(c);

			high = low + (range*p.high) / p.count - 1;
			low = low + (range*p.low) / p.count;

			for (; ; ) {
				if (high < HALF) {

				}
				else if (low >= HALF) {
					value -= HALF;  
					low -= HALF;
					high -= HALF;
				}
				else if (low >= Q1 && high < Q3) {
					value -= Q1;
					low -= Q1;
					high -= Q1;
				}
				else
					break;
				low <<= 1;
				high <<= 1;
				high++;
				value <<= 1;
				value += m_input.readbits(1) ? 1 : 0;
			}
		}

		return 0;
	}
private:
	vector<int> & m_output;
	BitsIO m_input;
	model m_model;
	int nsym;
};


