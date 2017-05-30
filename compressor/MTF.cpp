#include "MTF.h"
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;


MTF::MTF()
{
}
string MTF::getSymbols()
{
	sort(Symbols.begin(), Symbols.end());
	return Symbols;



}

void MTF::moveToFront(string l,vector<int>&final)
{   
	set<char>symbols;
	Symbols = "";
	
	for (int i = 0; i < l.length(); ++i)
	{
		
		symbols.insert(l[i]);
		
	}
	set<char>::iterator it;
	for (it = symbols.begin(); it != symbols.end(); ++it)
	{
		Symbols += (*it);
	}
	vector<int>vv;
	for (int i = 0; i < l.length(); ++i)
	{
		int idx = Symbols.find(l[i]);
		
		Symbols.erase(Symbols.begin()+idx);
		string b = "";
		b += l[i];
		b += Symbols;
		Symbols = b;
		vv.push_back(idx);
	}
	bool flag = false;
	
	int counter = 0;
	for (int i = 0; i < vv.size(); ++i)
	{
		if (!vv[i])
		{
			counter++;
		}
		else
		{
			if (counter)
			{
				vector<int>temp = convertTOBijective(counter);
				final.insert(final.end(), temp.begin(), temp.end());
				counter = 0;
				
			}
			vv[i]+= BIJECTIVEBASE - 1;
			final.push_back(vv[i]);

		}

	}
	if (counter)
	{
		vector<int>temp = convertTOBijective(counter);
		final.insert(final.end(), temp.begin(), temp.end());
		counter = 0;
	}
	





}
vector<int> MTF::convertTOBijective(long long int num)
{

	int dividend = num;
	//string columnName = String.Empty;
	int modulo;
	vector<int>runs;
	while (dividend > 0)
	{
		modulo = (dividend - 1) % BIJECTIVEBASE;
		runs.push_back(modulo);

		dividend = (int)((dividend - modulo) / BIJECTIVEBASE);
	}
	return runs;
	



}

MTF::~MTF()
{
}
