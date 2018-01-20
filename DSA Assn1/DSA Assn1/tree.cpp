#include "stdafx.h"
#include "tree.h"
#include <iostream>
#include <algorithm>
using namespace std;

Tree::Tree()
{
	root = NULL; // Intialise root node to NULL
}
Tree::~Tree() {};
int counter = 0;
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
}

void Tree::search(ItemType value,node *targetnode)
{
	if (targetnode == NULL)
	{
		cout << "Lost Target" << endl;
		return;
	}
	else if (targetnode->value == value)
	{
		cout << targetnode->value << endl;
	}
	if (value > targetnode->value)
	{
		cout << "R -> ";
		search(value, targetnode->right_node);
	}
	else if (value < targetnode->value)
	{
		cout << "L -> ";
		search(value, targetnode->left_node);
	}
}
void Tree::search(ItemType value)
{
	if (value == root->value)
	{
		cout << "Root -> " << value << endl;
	}
	search(value, root);
}

//Remove
Tree::node *Tree::minvaluenode(node *tempnode)
{
	node *current = new node;

	//While loop to see left-most(lowest value) leaf
	while (current->left_node != NULL)
	{
		current = current->left_node;
	}
	if (current->value == 0)
	{
		current = tempnode;
	}
	return current;
}
Tree::node *Tree::remove(node *root, ItemType value) //Target requested node --> link previous node to next node --> delete current node from memory
{
	if (root == NULL)
	{
		cout << "Target not found" << endl;
		return root; //Target not found
	}
	else if (value > root->value)
	{
		root->right_node = remove(root->right_node, value);
	}
	else if (value < root->value)
	{
		root->left_node = remove(root->left_node, value);
	}
	else if (value == root->value)
	{
		if (root -> right_node == NULL || root->left_node == NULL) // One or no children
		{
			node *tempnode1 = root->left_node ? root->left_node : root->right_node; // Sets tempnode1 to the node that ISN'T NULL
			if (tempnode1 == NULL) //No children
			{
				tempnode1 = root;
				root = NULL; //Completely deletes(nullifies) this node
			}
			else
			{
				*root = *tempnode1; //Sets its only child to replace itself
			}
		}
		else //Two children
		{
			node *tempnode1 = new node;
			tempnode1 = minvaluenode(root->right_node);
			root->value = tempnode1->value;
			root->right_node = remove(root->right_node, tempnode1->value);
		}
	}
	return root;
}
void Tree::remove(ItemType value)
{
	remove(root, value);
	root = rebalance(root); //Returns the balanced node with proper connected nodes
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
int Tree::printlevel(node *root, int level, int nth)
{
	if (root == NULL)
		return counter;
	if (level == 1)
	{
		counter++;
		if (counter == nth)
		{
			cout << "Node has value: " << root->value << endl;
		}
		
		return counter;
	}
	else if (level > 1)
	{
		printlevel(root->left_node, level - 1,nth);
		printlevel(root->right_node, level - 1,nth);
		return counter;
	}
}
void Tree::printlevelorder(node *root,int nth)
{
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
	{
		printlevel(root, i,nth);
	}
	counter = 0;
}
void Tree::displayNthnode(int nth)
{
	printlevelorder(root,nth);
}