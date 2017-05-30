#pragma once
extern int OFFSETSIZE;
extern int LENGTHSIZE;
extern int MINMATCH;
extern bool shortestOffset;
#define TOKEN 1
#define SYMBOL 0
#define RECENT 1
#define NOTRECENT 0
#define BIJECTIVEBASE 3
#include <string>

struct data {
	std::string str;
	int position;


};

struct comp {
	bool operator()(const struct data& x, const struct data& y) const
	{
		if (x.str < y.str)
		{
			return true;
		}

		else if (x.str == y.str)
		{
			return (x.position > y.position);
		}

		else
		{
			return false;
		}
	}
};