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
void Tree::search(ItemType value)
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
//Remove
Tree::node *Tree::minvaluenode(node *tempnode)
{
	node *current = new node;

	//While loop to see left-most(lowest value) leaf
	while (current->left_node != NULL)
	{
		current = current->left_node;
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
void Tree::displayNthnode()
{
	displayNthnode(root,3,0);
}
void Tree::displayNthnode(node *tempnode, ItemType nth, int counter)
{
	if (tempnode == NULL)
	{
		return;
	}
	counter++;
	if (counter == nth)
	{
		cout << tempnode->value << "<< Value" << endl;
		return;
	}
	displayNthnode(tempnode->left_node, nth,counter);
	counter++;
	displayNthnode(tempnode->right_node, nth, counter);

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