#include "stdafx.h"
#include "tree.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

Tree::Tree()
{
	root = NULL; // Intialise root node to NULL
}
Tree::~Tree() {};

Tree::node *Tree::insert(node *root,ItemType value)
{
	if (root == NULL) //Base case
	{
		node *root = new node;
		root->value = value;
		return root;
	}
	else if (value < root->value)
	{
		root->left_node = insert(root->left_node, value);
		root = rebalance(root);
	}
	else if (value >= root->value)
	{
		root->right_node = insert(root->right_node, value);
		root = rebalance(root);
	}
	return root;
}

void Tree::insert(int value)
{
	root = insert(root, value);
	fulldisplay();
}

int Tree::search(ItemType value,node *targetnode)
{
	int mode; //Decides whether to print out or not
	
	if (targetnode == NULL)
	{
		return 0;
	}
	else if (targetnode->value == value)
	{
		return 1;
	}
	
	mode = search(value, targetnode->left_node);
	if (mode == 1)
	{
		cout << "L -> ";
		//cout << targetnode->value << endl;
		return 1;
	}
	mode = search(value, targetnode->right_node);
	if (mode == 1)
	{
		cout << "R -> ";
		//cout << targetnode->value << endl;
		return 1;
	}
	return 0;
}
void Tree::traverse(ItemType value)
{
	int status = -1;
	if (root->value == value)
	{
		cout << "Root" << endl;
		return;
	}
	status = search(value, root);
	//cout << status << endl;
	if (status == 0)
	{
		cout << "Lost Target" << endl;
	}
	else if (status == 1) 
	{
		cout << value << endl;
	}
}

void Tree::remove(ItemType value) //Target requested node --> link previous node to next node --> delete current node from memory
{
	//TODO: Add code to handle deletion of root
	node *tempnode = new node; //Current node
	node *prevnode = new node; //Previous node
	tempnode = root;
	vector <int> direction; //Stores directional data; 1 denotes left,2 denotes right
	vector <int> ::iterator i;
	while (tempnode->value != value || tempnode == NULL)
	{
		if (value > tempnode->value)
		{
			direction.push_back(2);
			prevnode = tempnode;
			tempnode = tempnode->right_node;
		}
		else if (value < tempnode->value)
		{
			direction.push_back(1);
			prevnode = tempnode;
			tempnode = tempnode->left_node;
		}
	}
	if (tempnode == NULL)
	{
		cout << "Requested value unavailable" << endl;
		return;
	}
	//Removal branches
	//1)No children
	if (tempnode->left_node == NULL && tempnode->right_node == NULL)
	{
		if (direction.back() == 1) // Came from the left
		{
			prevnode->left_node = NULL;
		}
		else if (direction.back() == 2)
		{
			prevnode->right_node = NULL;
		}
		delete tempnode; //Memory Cleanup
	}
	//2)1 Child
	else if (tempnode->left_node == NULL) //1 Child on the right_node
	{
		prevnode->right_node = tempnode->right_node; //Links previous node to child node
		delete tempnode;
	}
	else if (tempnode->right_node == NULL)
	{
		prevnode->left_node = tempnode->left_node;
		delete tempnode;
	}
	//3)2 Children
	else
	{
		if (direction.back() == 1) //From the left
		{
			prevnode->left_node = tempnode->left_node;
			prevnode->left_node->right_node = tempnode->right_node;
		}
		else if (direction.back() == 2)
		{
			prevnode->right_node = tempnode->right_node;
			prevnode->right_node->left_node = tempnode->left_node;
		}
		delete tempnode;
	}
}

//Rebalancing code
int Tree::height(node *temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int l_height = height(temp->left_node);
		int r_height = height(temp->right_node);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}
int Tree::diff(node *temp)
{
	int l_height = height(temp->left_node);
	int r_height = height(temp->right_node);
	int factor = l_height - r_height;
	return factor;
}

Tree::node *Tree::leftrotate(node *nodeN)
{
	node *nodeC = new node;
	nodeC = nodeN->right_node;
	nodeN->right_node = nodeC->left_node;
	nodeC->left_node = nodeN;
	return nodeC;
}
Tree::node *Tree::rightrotate(node *nodeN)
{
	node *nodeC = new node;
	nodeC = nodeN->left_node;
	nodeN->left_node = nodeC->right_node;
	nodeC->right_node = nodeN;
	return nodeC;
}
Tree::node *Tree::leftrightrotate(node *nodeN)
{
	node *nodeC = new node;
	nodeC = nodeN->left_node;
	nodeN->left_node = leftrotate(nodeC);
	return rightrotate(nodeN);
}
Tree::node *Tree::rightleftrotate(node *nodeN)
{
	node *nodeC = new node;
	nodeC = nodeN->right_node;
	nodeN->right_node = rightrotate(nodeC);
	return leftrotate(nodeN);
}
Tree::node *Tree::rebalance(node *temp)
{
	int balance_factor = diff(temp);
	if (balance_factor > 1)
	{
		if (diff(temp->left_node) > 0)
			temp = rightrotate(temp);
		else
			temp = leftrightrotate(temp);
	}
	else if (balance_factor < -1)
	{
		if (diff(temp->right_node) > 0)
			temp = rightleftrotate(temp);
		else
			temp = leftrotate(temp);
	}
	return temp;
}
//Display
void Tree::fulldisplay(node *temp,int level)
{
	int i;
	if (temp != NULL) //Base case
	{
		fulldisplay(temp->right_node, level + 1);
		cout << "\n";
		if (temp == root)
		{
			cout << "Root -> ";
		}
		for (i = 0; i < level && temp != root; i++)
			cout << "       ";
		cout << temp->value;
		fulldisplay(temp->left_node, level + 1);
	}
}
void Tree::fulldisplay()
{
	fulldisplay(root, 1);
	cout << endl;
}
void Tree::displayNthnode()
{
	displayNthnode(root, 1);
}
void Tree::displayNthnode(node *tempnode, ItemType nth)
{
	if (tempnode == NULL)
	{
		return;
	}
	cout << tempnode->value << "," << endl;
	displayNthnode(tempnode->left_node, nth);
	displayNthnode(tempnode->right_node, nth);

}
void Tree::displayinasc()
{
	displayinasc(root);
}
void Tree::displayinasc(node *tempnode)
{
	if (tempnode == NULL)
	{
		return;
	}
	displayinasc(tempnode->left_node);
	cout << tempnode->value << ",";
	displayinasc(tempnode->right_node);

}