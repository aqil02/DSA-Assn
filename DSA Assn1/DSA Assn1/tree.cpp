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
		cout << "Tree is empty!" << endl;
		return;
	}
	if (value == root->value)
	{
		cout << "Root -> " << value << endl;
		status = 1;
	}
	search(value, root);
}

//Minvaluenode attempts to find lowest value in the tree,starting tempnode specified as a parameter
//It basically uses a while loop to keep traversing left until it reaches a NULL node(Means it hit the end)
//It then returns the current node
Tree::node *Tree::minvaluenode(node *tempnode)
{
	node *current = new node;
	current = tempnode;
	//While loop to see left-most(lowest value) leaf
	while (current->left_node != NULL)
	{
		current = current->left_node;
	}
	//if (current->value == 0) //Didn't need this??
	//{
	//	current = tempnode;
	//}
	return current;
}
//Remove(Dependant on Minvaluenode function)
//Traverses through the tree in a similar way to insert, in that it traverses left if the value is less than the current node's value, vice versa if more
//If it hits a NULL node, it means value cant be found and we simply return our targeted node, changing nothing in the tree
//Otherwise we check if it has 0,1 or 2 children and perform appropriate removal code
//Void function remove checks if the value exist in the tree or not first, unchecks the printstatus flag as it uses the search function
//If the value doesnt exist, we dont even run the recursive function and simply output an error message
Tree::node *Tree::remove(node *root, ItemType value) //Target requested node --> link previous node to next node --> delete current node from memory
{
	//if (root == NULL)
	//{
	//	cout << "Target not found" << endl; //Redundant code
	//	return root; //Target not found
	//}
	if (value > root->value)
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
//Height simply returns the height of the highest node starting from node temp
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
//Diff represents the balance factor, the difference between the left sub-tree and right sub-tree
//It takes height of left and right sub-tree, then subtracts and returns the balance factor
int Tree::diff(node *temp)
{
	int l_height = height(temp->left_node);
	int r_height = height(temp->right_node);
	int factor = l_height - r_height;
	return factor;
}
//Performs a standard left-rotate
Tree::node *Tree::leftrotate(node *nodeN)
{
	node *nodeC = new node;
	nodeC = nodeN->right_node;
	nodeN->right_node = nodeC->left_node;
	nodeC->left_node = nodeN;
	return nodeC;
}
//Performs a standard right rotate
Tree::node *Tree::rightrotate(node *nodeN)
{
	node *nodeC = new node;
	nodeC = nodeN->left_node;
	nodeN->left_node = nodeC->right_node;
	nodeC->right_node = nodeN;
	return nodeC;
}
//Performs a standard left-right rotate
Tree::node *Tree::leftrightrotate(node *nodeN)
{
	node *nodeC = new node;
	nodeC = nodeN->left_node;
	nodeN->left_node = leftrotate(nodeC);
	return rightrotate(nodeN);
}
//Performs a standard right-left rotate
Tree::node *Tree::rightleftrotate(node *nodeN)
{
	node *nodeC = new node;
	nodeC = nodeN->right_node;
	nodeN->right_node = rightrotate(nodeC);
	return leftrotate(nodeN);
}
//This takes in any node and rebalances it starting from node temp
//It checks if there are any differences more than 1 between the left and right sub-tree
//If there are, it performs the appropriate rotate based on whether the sub-tree is left or right heavy
//It then returns the node it was given at first, but with all following nodes balanced
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
//Full display consists of a recursive and void function
//Recursive function recursively renders the entire tree, with base case being the node being NULL
//It traverses the sub-tree until it hits a NULL node(dead-end), ending that instance of the function
//
//Void function simply calls the recursive function with default parameters
void Tree::fulldisplay(node *temp,int level)
{
	if (temp != NULL) //Base case
	{
		fulldisplay(temp->right_node, level + 1);
		cout << "\n";
		if (temp == root)
		{
			cout << "Root -> ";
		}
		for (int i = 0; i < level && temp != root; i++)
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
//Displayinasc basically prints the tree in-order, when used with a balanced tree, results in the numbers being printed in ascending order
//Overloaded function basically just calls it
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
//printlevel,printlevelorder and displayNthnode make up the displayNthnode
//print level takes in a starting node, level to print and nth value to be printed
//It is a recursive function with base cases, root == NULL and level == 1
//At each recursive stage, we input the same parameters except the level is subtracted by 1 until base case is reached
//When level == 1,it means we've reached one of that level's node
//Since we hit one of the nodes, we increment a coherent global variable named counter by 1 to represent the number of nodes read so far
//That node's value is ONLY printed when the counter matches the node number to be read, as it means that the requested node has been targetted

int Tree::printlevel(node *root, int level, int nth)
{
	if (root == NULL)
		return 0;
	if (level == 1)
	{
		counter++;
		if (counter == nth)
		{
			cout << "Node has value: " << root->value << endl;
		}
		
		return 0;
	}
	else if (level > 1)
	{
		printlevel(root->left_node, level - 1,nth);
		printlevel(root->right_node, level - 1,nth);
		return 0;
	}
}
//printlevelorder takes in a node(root by default to search entire tree) and nth node to be read
//First it finds the height of the highest node using the height function
//We then use a for loop to check each node level by level, up to the highest level, after which the for loop stops
//At the end of the search, the global counter must be set to 0 as the next few searches depends on the counter being 0 at the start of the search
void Tree::displayNthnode(int nth)
{
	int h = height(root);
	for (int i = 1; i <= h; i++)
	{
		printlevel(root, i,nth);
	}
	counter = 0;
}
