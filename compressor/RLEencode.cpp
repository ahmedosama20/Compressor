#include "RLEencode.h"
#define MINLENGTH 4

RLEencode::RLEencode()
{
}
string RLEencode::encode(string s)
{
	
	unsigned char counter = 1;
	string ans = "";
	int i;
	for ( i = 1; i < s.length(); ++i)
	{
		if (s[i] == s[i - 1]&&counter<=255)
		{
               counter++;

		}
		else
		{
			if (counter>MINLENGTH)
			{
				counter -= MINLENGTH;
				for (int j = 0; j < MINLENGTH; ++j)
				{
					ans += s[i - 1];
				}
				ans += counter;
			}
			else
			{
				for (int j = 0; j < counter; ++j)
				{
					ans += s[i- 1];
				}
			}
			counter = 1;
		}
	}
	if (counter>MINLENGTH)
	{
		counter -= MINLENGTH;
		for (int j = 0; j < MINLENGTH; ++j)
		{
			ans += s[i - 1];
		}
		ans += counter;
	}
	else
	{
		for (int j = 0; j < counter; ++j)
		{
			ans += s[i - 1];
		}
	}
	return ans;

}

RLEencode::~RLEencode()
{
}
