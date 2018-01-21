#pragma once

typedef int ItemType;

class Tree
{
private:
	struct node
	{
		ItemType value;
		node *left_node;
		node *right_node;
		node() :value(NULL),left_node(NULL), right_node(NULL) {} //Initialises all variables to be NULL to avoid NULLPTR errors(Uninitialised nodes cannot be read)
	};
	node *root;
public:
	//constructor
	Tree(); 
	//destructor
	~Tree();

	//Insert item to the tree
	//pre : value not already in tree, value is valid
	//post : node with value is added to the tree and balanced
	node *insert(node *root,ItemType value); 
	void insert(int value); //Overloaded

	//Remove node from the tree
	//pre : value exists in the tree, value is valid
	//post : node with this value is removed from tree, tree is balanced
	node *minvaluenode(node *node);
	node *remove(node* tempnode,ItemType value); 
	void remove(ItemType value); //Overloaded

	//Search tree for the node with the value, print directions
	//pre : value is valid and is an integer
	//post : outputs directions to the value, sets status flag to 1 or 0 depending on results
	void search(ItemType value,node *targetnode);
	void search(ItemType value); //Overloaded

	//Display in ascending order
	//pre : none
	//post : Displays numbers in the tree in ascending order
	void displayinasc(node *tempnode);
	void displayinasc();//Overloaded

	//Display Nth node
	//pre: nth is less than the total amount of nodes in tree
	//post: displays value of nth node
	int printlevel(node *root, int level, int nth);
	void displayNthnode(int nth);

	//Displays full tree
	//pre: none
	//post: Renders full tree
	void fulldisplay(node *tempnode, int level);
	void fulldisplay();//Overloaded

	//Rebalancing algorithm
	//Returns height of the node
	//pre: temp is a valid node
	//post: returns height of the node
	int height(node *temp); 

	//Returns balancing factor
	//pre: none
	//post: Returns the differences between the left and right balance factor
	int diff(node *temp);

	//Rotates nodes
	//pre: node is valid
	//post: returns node with proper rotations applied
	node *leftrotate(node *nodeN);
	node *rightrotate(node *nodeN);
	node *leftrightrotate(node *nodeN);
	node *rightleftrotate(node *nodeN);

	//Rebalances node given
	//pre: node is valid
	//post: returns a node with all the nodes balanced
	node *rebalance(node *temp);


	
};