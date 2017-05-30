#include "RLEDecode.h"


RLEDecode::RLEDecode(string& in, string& out, int m) : my_in(in), my_out(out)
{
	minmatch = m;

	int cntr = 1;
	my_out += in[0];
	for (int i = 1; i < in.size(); i++)
	{
		if (in[i] == in[i - 1])
		{
			cntr++;
			my_out += in[i];
			if (cntr == m)
			{
				i++;
				int count = (unsigned int)in[i];
				for (int j = 0; j < count; j++)
					my_out += in[i - 1];
				cntr = 1;

			}
		}
		else
		{
			my_out += in[i];
			cntr = 1;
		}

	}
}

RLEDecode::~RLEDecode()
{
}
