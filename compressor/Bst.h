#pragma once
struct node {
	int size;
	string &in;
	string &out;
	node* left;
	node* right;
	int rotation;
	int position;

	node(string &input, string &output, int size) : in(input), out(output)
	{
		this->size = size;
		left = NULL;
		right = NULL;
		rotation = 0;
		position = 0;
	}

	void insert(node* ptr)
	{
		node* t = this;
		while (true)
		{
			if (!lexicographical_compare(in.begin() + t->rotation, in.begin() + t->rotation + size, in.begin() + ptr->rotation, in.begin() + ptr->rotation + size))
			{
				t->position++;
				if (t->left == NULL)
				{
					t->left = ptr;
					break;
				}
				else
				{
					t = t->left;
				}
			}
			else
			{
				ptr->position++;
				if (t->right == NULL)
				{
					t->right = ptr;
					break;
				}
				else
				{
					t = t->right;
				}
			}
		}
	}
	void InOrder(node *root, int &pos) {
		if (root == NULL) {
			return;
		}
		InOrder(root->left, pos);// traverse lft subtree
		out[pos] = in[root->rotation - 1 + size];
		pos++;
		InOrder(root->right, pos);// traverse rt subtree
	}
};