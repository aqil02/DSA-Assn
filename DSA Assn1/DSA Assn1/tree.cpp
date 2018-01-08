#include "tree.h"
#include "stdafx.h"

Tree::Tree()
{
	root = NULL; // Intialise root node to NULL

};
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
		root->value = value; //Add value to root node
		node *left = new node;// Create new nodes for left and right of root pre-emptively
		node *right = new node;
		root->left_node = left;
		root->right_node = right;
	}

	else //(2)
	{
		node *tempnode = new node; //Used to store next targeted node
		tempnode = root;
		while (tempnode->value != value)
		{
			if (value < tempnode->value) //Less (3a)
			{
				//Run to see if predecessor exists
				if (tempnode->left_node->value == NULL)
				{
					tempnode = tempnode->left_node;
					tempnode->value = value;
					break; //(4)
				}
				else
				{
					tempnode = tempnode->left_node;
				}
			}
			else if (value > tempnode->value) //More (3b)
			{
				//Run to see if successor exits
				if (tempnode->right_node->value = NULL)
				{
					tempnode = tempnode->right_node;
					tempnode->value = value;
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
