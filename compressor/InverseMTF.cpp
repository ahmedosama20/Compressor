#include "InverseMTF.h"
#include<algorithm>


InverseMTF::InverseMTF()
{
}
string InverseMTF::inverseMoveToFront(vector<int> final,string Symbols)
{
	string l = "";
	int power = 1;
	int check = 0;
	
	for (int i = 0; i < final.size(); ++i)
	{
		if (final[i] < BIJECTIVEBASE)
		{
			check += ((final[i] + 1)*power);
			power *= BIJECTIVEBASE;

		}
		else
		{
			if (check)
			{
				for (int j = 0; j < check; ++j)
				{
					l += Symbols[0];
				}
				check = 0;
				power = 1;
			}
			final[i] -= (BIJECTIVEBASE - 1);
			l += Symbols[final[i]];
			string b = "";
			b += Symbols[final[i]];
			Symbols.erase(Symbols.begin() + final[i]);
			b += Symbols;
			Symbols = b;


		}
	}
	if (check)
	{
		for (int j = 0; j < check; ++j)
		{
			l += Symbols[0];
		}
	}
	return l;

}

InverseMTF::~InverseMTF()
{
}
