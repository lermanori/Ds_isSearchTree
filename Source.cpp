#include<iostream>

class node {
public:
	int data;
	node* left;
	node* right;

	node(int data, node* left = nullptr, node* right = nullptr) :data(data), left(left), right(right) {};

};


class checker {
public:
	node* max;
	node* min;
	bool status;

	checker(node* max, node* min, bool status) :max(max), min(min), status(status) {};
	checker(const checker& ch) :max(ch.max), min(ch.min), status(ch.status) {};
	checker(checker&& ch) :max(ch.max), min(ch.min), status(ch.status) {};

	checker(bool b):max(nullptr), min(nullptr), status(b) {};

};

class tree {
public:
	node* root;
	tree(const int* arr ,size_t n)
	{

		this->root = new node(arr[0],createSubTree(1,arr,n), createSubTree(2,arr,n));


	}
	node* createSubTree(int index,const int* arr,size_t n) 
	{
		if (arr[index] == -1||index >= n)
		{
			return nullptr;
		}
		else if ((arr[2*index+1] == -1 || 2 * index + 1 >= n)&& (arr[2 * index + 2] == -1 || 2 * index + 2 >= n))
		{
			return new node(arr[index]);
		}
		else
		{
			if (arr[2 * index + 1] == -1 || 2 * index + 1 >= n)
			{
				return new node(arr[index], nullptr, createSubTree(2 * index + 2, arr,n));

			}
			else if (arr[2 * index + 2] == -1 || 2 * index + 2 >= n)
			{
				return new node(arr[index], createSubTree(2 * index + 1, arr,n), nullptr);

			}
			else
			{
				return new node(arr[index], createSubTree(2 * index + 1, arr,n), createSubTree(2 * index + 2, arr,n));

			};

		}
	}
};



checker isSearchTree(node* root)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		return checker(root, root, true);
	}
	else
	{
		if (root->right == nullptr)
		{
			checker checkL = isSearchTree(root->left);
			if (checkL.max->data <= root->data&&checkL.status == true)
				return checker(root, checkL.max, true);
			else
				return false;
		}
		else if (root->left == nullptr) 
		{
			checker checkR = isSearchTree(root->right);
			if (checkR.min->data >= root->data&&checkR.status == true)
				return checker(checkR.min, root, true);
			else
				return false;
		}


		else
		{
		checker checkL = isSearchTree(root->left);
		checker checkR = isSearchTree(root->right);

		if (checkR.status == true &&checkL.status == true&&checkR.min->data >= root->data&& checkL.max->data <= root->data)
			return checker(checkR.min, checkL.max, true);
		else
			return false;

		}


	}
}
void main()
{
	int ori[] = {7,4,9,6,-1,-1,10};
	const int* pt = ori;

	tree tr(pt,7);

	checker  c = isSearchTree(tr.root);




}


