//Team Member's names: Aqil Ahmad Subahan, Lee ZhiYong
//Team Member's IDs: S10166743C, S10173753F

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
int counter = 0; //Global counter used for Nth node function, allows recursive function 
int status = -1; //Global status indicator used to check if search function returned a hit or not
int printstatus = 1; //Global flag to ensure functions that utilise other functions do not invoke any print functions (e.g. Insert using Search for value validation)
//Insert function
//This function is seperated into two, a recursive function and a void function.
//Recursive function does the actual search using the simple principle of a BST in that left subnode is smaller than root while right is bigger
//Thus, first it checks whether the inserted value is bigger or smaller than root, than traverses in that direction
//Eventually, it reaches an empty node where it can be inserted, this is the base case at which a new node is created and inserted
//It then balances the tree using the rebalance function
//The void function introduces validation to ensure duplicate values cannot be entered using the search function to see if value is already in tree
//Variable status stores the outcome of the search(successful or not) and allows us to see if the value is already in the tree
//From there, we can decide whether or not to induce the recursive function in the first place or not
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
	printstatus = 0;
	search(value);
	if (status == 1)
	{
		cout << "Value already exists in tree!" << endl;
		status = -1;
		return;
	}
	else if (status == 0) 
	{
		root = insert(root, value);
		cout << "Successfully added!" << endl;
		status = -1;
	}
	printstatus = 1;
}
//Search function is made up of a recursive function and void function to activate the recursive function
//Recursive function works with the same principles as the insert function(If the value is bigger than the root, traverse to the right subnode, smaller means left subnode)
//After each traversal, we show what direction the program takes with cout
//If it hits a NULL node, it means search did not fine the value, and that we lost the target
//Otherwise it means we hit the value we need and print out the value and change the global variable status to 1 to tell the rest of the program that the search succeeded
//Void function checks for an empty tree first, then checks if the value equals the tree, this saves resources as we dont have to access the recursive function if we know the root node has the value
//Otherwise, the void function takes a value and enters it into the recursive function
void Tree::search(ItemType value,node *targetnode)
{
	if (targetnode == NULL)
	{
		if (printstatus == 1)
		{
			cout << "Lost Target" << endl;
		}
		status = 0;
		return;
	}
	else if (targetnode->value == value)
	{
		cout << targetnode->value << endl;
		status = 1;
	}
	if (value > targetnode->value)
	{
		if (printstatus == 1)
		{
			cout << "R -> ";
		}
		search(value, targetnode->right_node);
	}
	else if (value < targetnode->value)
	{
		if (printstatus == 1)
		{
			cout << "L -> ";
		}
		search(value, targetnode->left_node);
	}
}
void Tree::search(ItemType value)
{
	if (root == NULL)
	{
		status = 0;
		return;
	}
	if (value == root->value)
	{
		cout << "Root -> " << value << endl;
		status = 1;
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
	printstatus = 0;
	search(value);
	if (status == 0)
	{
		cout << "Value does not exist in tree!" << endl;
		status = -1;
		return;
	}
	else if(status == 1)
	{
		remove(root, value);
		cout << "Successfully removed" << endl;
		root = rebalance(root); //Returns the balanced node with proper connected nodes
		status = -1;
	}
	printstatus = 1;
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