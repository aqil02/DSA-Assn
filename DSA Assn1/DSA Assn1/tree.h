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
		node() :value(NULL),left_node(NULL), right_node(NULL) {}
	};
	node *root;
public:
	Tree(); 
	~Tree();
	//Insert
	node *insert(node *root,ItemType value); 
	void insert(int value); //Overloaded

	//Remove
	node *minvaluenode(node *node);
	node *remove(node* tempnode,ItemType value); 
	void remove(ItemType value); //Overloaded

	//Search
	void search(ItemType value,node *targetnode);
	void search(ItemType value); //Overloaded

	//Display in ascending order
	void displayinasc(node *tempnode);
	void displayinasc();//Overloaded

	//Display Nth node
	int printlevel(node *root, int level, int nth);
	void displayNthnode(int nth);

	//Displays full tree
	void fulldisplay(node *tempnode, int level);
	void fulldisplay();//Overloaded

	//Rebalancing algorithm
	int height(node *temp); 
	int diff(node *temp);
	node *leftrotate(node *nodeN);
	node *rightrotate(node *nodeN);
	node *leftrightrotate(node *nodeN);
	node *rightleftrotate(node *nodeN);
	node *rebalance(node *temp);


	
};