#include "InverseBWT.h"
#include <iostream>
#include <set>

struct data2 {
	char str;
	int position;
};

struct comp2 {
	bool operator()(const struct data2& x, const struct data2& y) const
	{
		if (x.str < y.str)
		{
			return true;
		}

		else
		{
			return (x.position < y.position);
		}

	}
};

InverseBWT::InverseBWT(string & in, string & out, int & ini)
{
	size = in.size();
	out.resize(size);
	T = new int[size];
	set<data2, comp2> root;


	for (int x = 0; x < size; x++)
	{
		root.insert({ in[x], x });
	}

	int j = 0;
	for (set<data2, comp2>::iterator t = root.begin(); t != root.end(); t++)
	{
		T[(*t).position] = j;
		j++;
	}

	for (int i = size - 1; i >= 0; i--) {
		out[i] = in[ini];
		ini = T[ini];
	}

}

InverseBWT::~InverseBWT()
{
	delete[] T;
}
