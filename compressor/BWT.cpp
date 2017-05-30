#include "BWT.h"
#include <algorithm>
#include "Bst.h"





BWT::BWT(string &in, string &out, int &outi) : thein(in), theout(out)
{
	int size = in.size();
	out.resize(size);
	string input = in;
	input += input;
	node* root = new node(input,out, size);
	
	



	for (int i = 1; i < size; i++)
	{
		node* t = new node(input,out, size);
		t->rotation = i;
		root->insert(t);
	}

	outi = root->position;
	int x = 0;
	root->InOrder(root, x);
		
	
}

BWT::~BWT()
{
	
}
