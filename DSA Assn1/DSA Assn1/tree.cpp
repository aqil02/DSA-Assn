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
void Tree::search(ItemType value)
{
	//Parse through tree to find intended value
	node *tempnode = new node;
	node *prevnode = new node;
	tempnode = root;
	int direction;
	int statuscode = -1; // 0 represents found, 1 represents not found
	if (root->value == value)
	{
		cout << "Root" << endl;
	}
	while (tempnode->value != value)
	{

		if (value > tempnode->value)
		{
			if (tempnode->right_node == NULL)
			{
				cout << "Target not found" << endl;
				statuscode = 0;
				break;
			}
			prevnode = tempnode;
			tempnode = tempnode->right_node;
			direction = 0; //Signifies direction as right
			cout << "R -> ";
		}
		else if (value < tempnode->value)
		{
			if (tempnode->left_node == NULL)
			{
				cout << "Target not found" << endl;
				statuscode = 0;
				break;
			}
			prevnode = tempnode;
			tempnode = tempnode->left_node;
			direction = 1; //Signifies direction as left
			cout << "L -> ";
		}
	}
	if (statuscode != 0)
	{
		cout << "(" << value << ")" << endl;
	}
}
void Tree::remove(ItemType value)
{
	search(value);
}
void Tree::fulldisplay()
{

}
