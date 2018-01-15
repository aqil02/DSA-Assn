#include "stdafx.h"
#include "tree.h"
#include <iostream>

using namespace std;

Tree::Tree()
{
	root = NULL; // Intialise root node to NULL
}
Tree::~Tree() {};

void Tree::insert(ItemType value)
{
	//Check if Root node is null --> if it is, add this value to that (1)

	//Else check if value is lesser or more than root --> (2)
	//Less --> Check the left node (Predecessor) and see if it has any children(3a)
	//More --> Check the right node (Successor) and see if it has any children(3b)
	//Stop when less or more and the corresponding direction is empty (4)
	//Create a new node at that empty area and insert the value into it
	if (root == NULL) //(1)
	{
		node *tempnode = new node;
		tempnode->value = value;
		root = tempnode; //Add value to root node
	}

	else //(2)
	{

		node *tempnode = new node; //Used to store next targeted node
		node *valuenode = new node; //Used to store new value
		valuenode->value = value;
		tempnode = root;
		while (tempnode->value != value)
		{
			if (value < tempnode->value) //Less (3a)
			{
				//Run to see if predecessor exists
				if (tempnode->left_node == NULL) //Doesnt exist
				{
					tempnode->left_node = valuenode;
					break;
				}
				else
				{
					tempnode = tempnode->left_node;
				}
			}
			else if (value > tempnode->value) //More (3b)
			{
				//Run to see if successor exists
				if (tempnode->right_node == NULL)
				{
					tempnode->right_node = valuenode;
					break; //(4)
				}
				else
				{
					tempnode = tempnode->right_node;
				}
			}
		}
	}
};
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
		cout << "L " << endl;
		cout << targetnode->value << endl;
		return 1;
	}
	mode = search(value, targetnode->right_node);
	if (mode == 1)
	{
		cout << "R " << endl;
		cout << targetnode->value << endl;
		return 1;
	}
	return 0;
}
void Tree::traverse(ItemType value)
{
	if (root->value == value)
	{
		cout << "Root" << endl;
		return;
	}
	search(value, root);
	cout << value << endl;
}
void Tree::remove(ItemType value) //Target requested node --> link previous node to next node --> delete current node from memory
{
	node *tempnode = new node; //Current node
	node *prevnode = new node; //Previous node
	tempnode = root;
	int statuscode = -1; //Refer to search
	//Target requested node
	if (root->value = value)
	{
		
	}
	while (tempnode->value != value)
	{

	}
}
void Tree::fulldisplay()
{

}
