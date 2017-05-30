#pragma once
#include <iostream>

#define MAX 0xFFFFFFFFU
#define HALF 0x80000000U
#define Q1 0x40000000U
#define Q3 0xC0000000U

struct prob {
	unsigned int low;
	unsigned int high;
	unsigned int count;
};


	struct model
{
	int size; 
	unsigned int* cumulative_frequency;

	model(int sz)
	{
		size = sz + 2;
		cumulative_frequency = new unsigned int[size];

		for (int i = 0; i < size; i++)
			cumulative_frequency[i] = i;
	}

	void update(int c)
	{
		for (int i = c + 1; i < size; i++)
			cumulative_frequency[i]++;


	}
	prob getProbability(int c)
	{
		prob p = { cumulative_frequency[c], cumulative_frequency[c + 1], cumulative_frequency[size - 1] };

			update(c);

		return p;
	}
	prob getChar(unsigned int scaled_value, int &c)
	{

		for (int i = 0; i < size - 1; i++)
			if (scaled_value < cumulative_frequency[i + 1]) {
				c = i;
				prob p = { cumulative_frequency[i], cumulative_frequency[i + 1],cumulative_frequency[size - 1] };

					update(c);
				return p;
			}

	}
	unsigned int getCount()
	{
		return cumulative_frequency[size - 1];
	}


};
